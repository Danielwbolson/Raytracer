
#ifndef PARSE_H_
#define PARSE_H_

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#include "Sphere.h"
#include "Scene.h"
#include "Camera.h"

#include "Light.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "AmbientLight.h"

#include "Vector.h"

static Scene* Parse(std::string fileName) {
    FILE *fp;
    long length;
    char line[1024]; //Assumes no line is longer than 1024 characters!

    // open the file containing the scene description
    fp = fopen(fileName.c_str(), "r");

    // check for errors in opening the file
    if (fp == NULL) {
        fprintf(stderr, "Can't open file '%s'\n", fileName.c_str());
    }

    // determine the file size (this is optional -- feel free to delete the 4 lines below)
    fseek(fp, 0, SEEK_END); // move position indicator to the end of the file;
    length = ftell(fp);  // return the value of the current position
    //fprintf(stderr, "File '%s' is %ld bytes long.\n\n", fileName.c_str(), length);
    fseek(fp, 0, SEEK_SET);  // move position indicator to the start of the file

    Scene* scene = new Scene();

    //Loop through reading each line
    while (fgets(line, 1024, fp)) { //Assumes no line is longer than 1024 characters!
        if (line[0] == '#') {
            //fprintf(stderr, "Skipping comment: %s", line);
            continue;
        }

        char command[100];
        int fieldsRead = sscanf(line, "%s ", command); //Read first word in the line (i.e., the command type)
        std::string obj = std::string(command);

        if (fieldsRead < 1) { //No command read
         //Blank line
            continue;
        }

        if (strcmp(command, "camera") == 0) { //If the command is a camera
            float px, py, pz;
            float dx, dy, dz;
            float ux, uy, uz;
            float ha;
            sscanf(line, "camera %f %f %f %f %f %f %f %f %f %f",
                &px, &py, &pz, &dx, &dy, &dz, &ux, &uy, &uz, &ha);
            //fprintf(stderr,
            //    "Camera:\n"
            //    "  Position: %f %f %f\n"
            //    "  Direction: %f %f %f\n"
            //    "  Up: %f %f %f\n"
            //    "  HalfHeight Angle: %f\n",
            //    px, py, pz, dx, dy, dz, ux, uy, uz, ha);
            
            Vector right = Vector(ux, uy, uz).Cross(Vector(dx, dy, dz)).Normalize();
            Vector up = Vector(dx, dy, dz).Cross(Vector(right.x, right.y, right.z)).Normalize();


            Camera* cam = new Camera(Vector(px, py, pz), Vector(dx, dy, dz).Normalize(), up, ha);

            scene->camera = cam;
        }
        else if (strcmp(command, "film_resolution") == 0) { // If the command is a film_resolution command
            int width, height;
            sscanf(line, "film_resolution %d %d", &width, &height);
            //fprintf(stderr, "Film_resolution is (%d, %d)\n", width, height);

            scene->width = width;
            scene->height = height;
        }
        else if (strcmp(command, "sphere") == 0) { // If the command is a sphere command
            float x, y, z, r;
            sscanf(line, "sphere %f %f %f %f", &x, &y, &z, &r);
            //fprintf(stderr, "Sphere at position (%f,%f,%f) with radius %f\n", x, y, z, r);

            scene->surfaces.push_back(new Sphere(Vector(x, y, z), r));
        }
        else if (strcmp(command, "background") == 0) { // If the command is a background command
            float r, g, b;
            sscanf(line, "background %f %f %f", &r, &g, &b);
            //fprintf(stderr, "Background color of (%f,%f,%f)\n", r, g, b);

            scene->background = new Vector(r, g, b);
        }
        else if (strcmp(command, "output_image") == 0) { // If the command is an output_image command
            char outFile[1024];
            sscanf(line, "output_image %s", outFile);
            //fprintf(stderr, "Render to file named: %s\n", outFile);

            scene->image_path = new char[1024];
            scene->image_path = strcpy(scene->image_path, outFile);
        }
        else if (strcmp(command, "material") == 0) { // If the command is a material
            float ar, ag, ab; // ambient coefficients
            float dr, dg, db; // diffuse coefficients
            float sr, sg, sb, ns; // specular coefficients
            float tr, tg, tb, ior; // transmissiveness and index of refraction

            sscanf(line, "material %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
                &ar, &ag, &ab, &dr, &dg, &db, &sr, &sg, &sb, &ns, &tr, &tg, &tb, &ior);
            //fprintf(stderr,
            //    "Material:\n"
            //    "  Ambient coefficients: %f, %f, %f\n"
            //    "  Diffuse coefficients: %f, %f, %f\n"
            //    "  Specular coefficients: %f, %f, %f, %f\n"
            //    "  Transmissive coefficients: %f, %f, %f, %f\n",
            //    ar, ab, ag, dr, dg, db, sr, sg, sb, ns, tr, tg, tb, ior);

            scene->materials.push_back(new Material(Vector(ar, ag, ab), Vector(dr, dg, db), Vector(sr, sg, sb), ns, Vector(tr, tg, tb), ior));
        }
        else if (strcmp(command, "directional_light") == 0) { // If the command is a directional light
            float r, g, b, dx, dy, dz;
            sscanf(line, "directional_light %f %f %f %f %f %f",
                &r, &g, &b, &dx, &dy, &dz);
            //fprintf(stderr,
            //    "Directional Light:\n"
            //    "  Color: %f %f %f\n"
            //    "  Direction: %f %f %f\n",
            //    r, g, b, dx, dy, dz);

            scene->lights.push_back(new DirectionalLight(Vector(r, g, b), Vector(dx, dy, dz).Normalize()));
        }
        else if (strcmp(command, "spot_light") == 0) { // If the command is a point_light
            float r, g, b;
            float px, py, pz;
            float dx, dy, dz;
            float angle1, angle2;
            sscanf(line, "spot_light %f %f %f %f %f %f %f %f %f %f %f",
                &r, &g, &b, &px, &py, &pz, &dx, &dy, &dz, &angle1, &angle2);
            //fprintf(stderr,
            //    "Spot Light:\n"
            //    "  Color: %f %f %f\n"
            //    "  Position: %f %f %f\n"
            //    "  Direction: %f %f %f\n"
            //    "  Angles: %f %f\n",
            //    r, g, b, px, py, pz, dx, dy, dz, angle1, angle2);

            scene->lights.push_back(new SpotLight(Vector(r, g, b), Vector(px, py, pz), Vector(dx, dy, dz).Normalize(), angle1, angle2));
        }
        else if (strcmp(command, "point_light") == 0) { // If the command is a spot_light
            float r, g, b, x, y, z;
            sscanf(line, "point_light %f %f %f %f %f %f",
                &r, &g, &b, &x, &y, &z);
            //fprintf(stderr,
            //    "Point Light:\n"
            //    "  Color: %f %f %f\n"
            //    "  Position: %f %f %f\n",
            //    r, g, b, x, y, z);

            scene->lights.push_back(new PointLight(Vector(r, g, b), Vector(x, y, z)));
        }
        else if (strcmp(command, "ambient_light") == 0) { // If the command is a ambient_light
            float r, g, b;
            sscanf(line, "ambient_light %f %f %f", &r, &g, &b);
            //fprintf(stderr,
            //    "Ambient Light:\n"
            //    "  Color: %f %f %f\n",
            //    r, g, b);

            scene->lights.push_back(new AmbientLight(Vector(r, g, b)));
        }
        else if (strcmp(command, "max_depth") == 0) { // If the command is a max_depth
            float depth;
            sscanf(line, "max_depth %f", &depth);
            //fprintf(stderr, "Max Depth: %f\n", depth);

            scene->max_depth = depth;
        }
        else {
            fprintf(stderr, "WARNING. Do not know command: %s\n", command);
        }
    }
    return scene;
}

#endif