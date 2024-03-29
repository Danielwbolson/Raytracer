
#define _USE_MATH_DEFINES

#include "image.h"
#include "Vector.h"
#include "Parse.h"
#include "Scene.h"
#include "pixel.h"
#include "Ray.h"
#include "Intersection.h"

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string>
#include <omp.h>
#include <chrono>

#define STB_IMAGE_IMPLEMENTATION //only place once in one .cpp file
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION //only place once in one .cpp files
#include "stb_image_write.h"

Image RayCast(const Scene&);
Ray RayThruPixel(const Camera&, const float, const float, const int, const int);
bool FindIntersection(const Ray&, const Scene&, Intersection&);
Vector EvaluateRayTree(const Scene&, const Ray&, int);
Vector ApplyLightingModel(const Scene&, const Ray&, const Intersection&, int);
Ray Refract(const Ray&, const Intersection&);

int main(int argc, const char * argv[]) {
    
    // First argument is filename
    argc--; argv++;

    Scene scene = Scene();

    if (*argv != NULL) {
        fprintf(stderr, "Starting parsing of file\n");
        scene = Parse(scene, *argv);
        fprintf(stderr, "File parsing complete\n");
    }
    else {
        fprintf(stderr, "No scene file supplied\n");
        return 0;
    }

    fprintf(stderr, "Setting up camera variables\n");
    scene.camera.Setup(scene.width, scene.height);

    auto start = std::chrono::high_resolution_clock::now();
    fprintf(stderr, "Starting raycast\n");
    Image img = RayCast(scene);
    fprintf(stderr, "Finished raycast\n");
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    fprintf(stderr, "Raycasting portion took %f seconds\n", duration.count() / 1000.0f);
    
    char* chr = _strdup(scene.image_path.c_str());
    img.Write(chr);
    fprintf(stderr, "Image outputted\n");

    delete chr;
    return 0;
}

Image RayCast(const Scene& scene) {
    int w = scene.width;
    int h = scene.height;

    Image img = Image(w, h);

#pragma omp parallel num_threads(8)
    {
        Ray ray = Ray();

#pragma omp for schedule(guided)
        for (int i = 0; i < w; i ++) {
            if (i % (w / 20) == 0) {
                fprintf(stderr, "  - raycast %d percent done\n", (int)(i / (float)w * 100));
            }
            for (int j = 0; j < h; j++) {
                Vector col = Vector(0, 0, 0);
                float weightTot = 0;

                // Jittered supersampling
                for (int x = -2; x < 2; x++) {
                    for (int y = -2; y < 2; y++) {
                        float h_x = x * 0.5f;
                        float h_y = y * 0.5f;

                        float r_x = (((float)rand()) / ((float)RAND_MAX) * 0.5f) + h_x + i;
                        float r_y = (((float)rand()) / ((float)RAND_MAX) * 0.5f) + h_y + j;

                        float r = abs(r_x);
                        if (r_x >= w)
                            r = abs(w - 1 - abs(r_x - w - 1));

                        float c = abs(r_y);
                        if (r_y >= h)
                            c = abs(h - 1 - abs(r_y - h - 1));

                        float d = 1.0 / img.Distance(r, c, i, j);
                        weightTot += d;

                        // Shoot rays
                        ray = RayThruPixel(scene.camera, r, c, w, h);
                        col += d * EvaluateRayTree(scene, ray, 0);
                    }
                }

                // After our jittered supersampling
                col = col / weightTot;

                Pixel p;
                p.SetClamp(255 * col.x, 255 * col.y, 255 * col.z);
                img.GetPixel(i, j) = p;
            }
        }
    }

    fprintf(stderr, "  - raycast 100 percent done\n");

    return img;
}

Ray RayThruPixel(const Camera& cam, const float x, const float y, const int width, const int height) {
    Vector p_plane = cam.TopLeft() + cam.PixelWidth()*x*cam.Right() - cam.PixelWidth()*y*cam.Up();
    Vector v = (p_plane - cam.Position()).Normalize();

    return Ray(cam.Position(), v);
}

bool FindIntersection(const Ray& r, const Scene& s, Intersection& inter) {

    bool intersect = false;
    float dist = INFINITY;
    Intersection check;

    // Gets closest intersection
    for (int i = 0; i < s.surfaces.size(); i++) {
        if (s.surfaces[i]->IsAnIntersection(r, check)) {

            intersect = true;
            float newDist = check.point.Distance(r.point);
            if (newDist < dist) {
                inter = check;
                dist = newDist;
            }
        }
    }

    if (intersect)
        return true;
    else
        return false;
}

Vector EvaluateRayTree(const Scene& s, const Ray& r, int counter) {
    if (counter > s.max_depth) return Vector(0, 0, 0);
    counter++;

    Intersection hit = Intersection();

    if (FindIntersection(r, s, hit))
        return ApplyLightingModel(s, r, hit, counter);
    else
        return s.background;
}

Vector ApplyLightingModel(const Scene& s, const Ray& r, const Intersection& hit, int counter) {
    Vector c = Vector(0, 0, 0);

    // add up our lights coloring in the scene
    for (int i = 0; i < s.lights.size(); i++) {
        // specular and diffuse
        c += s.lights[i]->LightShading(hit, s);
    }

    Vector reflect = (-r.direction).Reflection(hit.normal);
    Ray mirror = Ray(hit.point + reflect * 0.0001f, reflect);
    c += hit.material.Specular() * EvaluateRayTree(s, mirror, counter);

    Ray glass = Refract(r, hit);
    c += hit.material.Transmissive() * EvaluateRayTree(s, glass, counter);
    return c;
}

Ray Refract(const Ray& r, const Intersection& i) {
    Vector n = i.normal;
    Vector dir = r.direction;
    float n_i;
    float n_r;

    if (n.Dot(dir) < 0) { // entering a surface
        n_i = 1.0f;
        n_r = i.material.IofR();
    }
    else {
        n = -n;
        n_i = i.material.IofR();
        n_r = 1.0f;
    }

    Vector part_1 = (n_i * (dir - n * (dir.Dot(n)))) / n_r;
    float part_2 = 1.0 - ((n_i * n_i) * (1.0 - (dir.Dot(n) * dir.Dot(n)))) / (n_r * n_r);
    float sqrt_part_2 = (float)sqrt(part_2);

    Vector refract = (part_1 - n * sqrt_part_2).Normalize();

    return Ray(i.point + refract * 0.0001f, refract);
}