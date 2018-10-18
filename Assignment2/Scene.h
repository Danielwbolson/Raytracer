
#ifndef SCENE_H_
#define SCENE_H_

#include "Camera.h"
#include "Surface.h"
#include "Material.h"
#include "Light.h"
#include "Vector.h"
#include <string>

#include <vector>

class Light;

class Scene {
public:
    int width;
    int height;
    float max_depth;
    Camera camera;
    std::vector<Surface*> surfaces;
    std::vector<Material> materials;
    std::vector<Light*> lights;
    Vector background;
    std::string image_path;

    Scene() : width(640), height(480), max_depth(5), 
        camera{ Camera(Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), 45) }, 
        background{ Vector(0, 0, 0) }{

    }

    ~Scene() {
        surfaces.clear();
        surfaces.empty();

        materials.clear();
        materials.empty();

        lights.clear();
        lights.empty();
    }
};

#endif