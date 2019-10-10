
#ifndef DIRECTIONAL_LIGHT_H_
#define DIRECTIONAL_LIGHT_H_

#include "Light.h"

class DirectionalLight : public Light {
private:
    Vector direction;

public:
    DirectionalLight();
    DirectionalLight(Vector, Vector);

    Vector Direction() const { return direction; }

    Vector LightShading(const Intersection&, const Scene&) const;
    bool Intersect(const Intersection&, const Scene&) const;

};

#endif