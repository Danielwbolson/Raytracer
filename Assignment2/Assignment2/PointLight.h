
#ifndef POINT_LIGHT_H_
#define POINT_LIGHT_H_

#include "Light.h"

class PointLight : public Light {
private:
    Vector position;

public:
    PointLight();
    PointLight(Vector, Vector);

    Vector Position() { return position; }

    Vector LightShading(Intersection*, Scene*);
    bool Intersect(Intersection*, Scene*);
};

#endif