
#ifndef LIGHT_H_
#define LIGHT_H_

#include "Vector.h"
#include "Ray.h"
#include "Camera.h"
#include "Scene.h"

#include <stdio.h>

class Scene;

class Light {
protected:
    Vector color;

public:
    virtual Vector LightShading(const Intersection&, const Scene&) const = 0;
    virtual bool Intersect(const Intersection&, const Scene&) const = 0;
};

#endif