
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

#define STB_IMAGE_IMPLEMENTATION //only place once in one .cpp file
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION //only place once in one .cpp files
#include "stb_image_write.h"

Image* RayCast(Scene*);
Ray* RayThruPixel(Camera*, float, float, int, int);
bool FindIntersection(Ray*, Scene*, Intersection*, Intersection*);
Vector CalculateColor(Intersection*, Scene*);

int main(int argc, const char * argv[]) {
    
    // First argument is filename
    argc--; argv++;

    Scene* scene = new Scene();

    if (*argv != NULL) {
        fprintf(stderr, "Starting parsing of file\n");
        scene = Parse(*argv);
        fprintf(stderr, "File parsing complete\n");

        for (int i = 0; i < scene->surfaces.size(); i++) {
            scene->surfaces[i]->material = scene->materials[i];
        }
        fprintf(stderr, "Set all surface's materials\n");
    }
    else {
        fprintf(stderr, "No scene file supplied\n");
        delete scene;
        return 0;
    }

    Image* img = new Image(scene->width, scene->height);

    fprintf(stderr, "Setting up camera variables\n");
    scene->camera->Setup(scene->width, scene->height);

    fprintf(stderr, "Starting raycast\n");
    img = RayCast(scene);
    fprintf(stderr, "Finished raycast\n");
    
    img->Write(scene->image_path);
    fprintf(stderr, "Image outputted\n");
    delete img;
    delete scene;

    return 0;
}

Image* RayCast(Scene* scene) {
    int w = scene->width;
    int h = scene->height;

    Image* img = new Image(w, h);
    Intersection* hit = new Intersection();
    Intersection* check = new Intersection();
    Ray* ray = new Ray();

    for (int i = 0; i < w; i++) {
        if (i % (w / 20) == 0) {
            fprintf(stderr, "  - raycast %d percent done\n", (int)(i / (float)w * 100));
        }
        for (int j = 0; j < h; j++) {
            ray = RayThruPixel(scene->camera, i, j, w, h);
            if (FindIntersection(ray, scene, hit, check)) {
                Vector v = CalculateColor(hit, scene);
                img->GetPixel(i, j) = Pixel(v.x, v.y, v.z);
            }
            else {
                Pixel p = Pixel(scene->background->x * 255, scene->background->y * 255, scene->background->z * 255);
                img->GetPixel(i, j) = p;
            }
        }
    }

    fprintf(stderr, "  - raycast 100 percent done\n");

    delete hit;
    delete ray;
    delete check;

    return img;
}

Ray* RayThruPixel(Camera* cam, float x, float y, int width, int height) {
    Vector p_plane = cam->TopLeft() + cam->PixelWidth()*x*cam->Right() - cam->PixelWidth()*y*cam->Up();
    Vector v = (p_plane - cam->Position()).Normalize();

    Ray* ray = new Ray(p_plane, v);

    return ray;
}

bool FindIntersection(Ray* r, Scene* s, Intersection* inter, Intersection* check) {
    std::vector<Intersection> intersects;

    for (int i = 0; i < s->surfaces.size(); i++) {
        if (s->surfaces[i]->IsAnIntersection(r, check)) {
            intersects.push_back(*check);
        }
    }

    if (intersects.size() == 0)
        return false;

    float dist = INFINITY;
    int closest_index = 0;
    for (int i = 0; i < intersects.size(); i++) {
        float temp_dist = r->point.Distance(intersects[i].point);
        if (temp_dist < dist) {
            dist = temp_dist;
            closest_index = i;
        }
    }

    *inter = intersects[closest_index];

    return true;
}

Vector CalculateColor(Intersection* h, Scene* s) {
    // Cache variables
    Vector c = Vector(0, 0, 0);

    // add up our lights coloring in the scene
    for (int i = 0; i < s->lights.size(); i++) {
        c += s->lights[i]->LightShading(h, s);
    }

    Pixel p;

    p.SetClamp(c.x, c.y, c.z);

    c = Vector(p.r, p.g, p.b);
   
    return c;
}

