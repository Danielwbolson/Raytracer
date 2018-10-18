
#ifndef POINT_LIGHT_H_
#define POINT_LIGHT_H_

#include "Light.h"

class PointLight : public Light {
private:
    Vector position;

public:
    PointLight();
    PointLight(Vector, Vector);

    Vector Position() const { return position; }

    Vector LightShading(const Intersection&, const Scene&) const;
    bool Intersect(const Intersection&, const Scene&) const;
};

#endif