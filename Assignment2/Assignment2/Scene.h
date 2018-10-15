
#ifndef SCENE_H_
#define SCENE_H_

#include "Camera.h"
#include "Surface.h"
#include "Material.h"
#include "Light.h"
#include "Vector.h"

#include <vector>

class Light;

class Scene {
public:
    int width;
    int height;
    float max_depth;
    Camera* camera;
    std::vector<Surface*> surfaces;
    std::vector<Material*> materials;
    std::vector<Light*> lights;
    Vector* background;
    char* image_path;

    Scene() : width(640), height(480), max_depth(5), 
        camera{ new Camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 45) }, 
        background(nullptr), image_path(nullptr) {

    }

    ~Scene() {
        surfaces.clear();
        surfaces.empty();

        materials.clear();
        materials.empty();

        lights.clear();
        lights.empty();

        delete camera;
        delete background;
        delete image_path;
    }
};

#endif