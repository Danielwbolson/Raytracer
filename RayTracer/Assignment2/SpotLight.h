
#ifndef SPOT_LIGHT_H_
#define SPOT_LIGHT_H_

#include "Light.h"

class SpotLight : public Light {
private:
    Vector position, direction;
    float theta, phi;

public:
    SpotLight();
    SpotLight(Vector, Vector, Vector, float, float);

    Vector Position() const { return position; }
    Vector Direction() const { return direction; }
    float Theta() const { return theta; }
    float Phi() const { return phi; }

    Vector LightShading(const Intersection&, const Scene&) const;
    bool Intersect(const Intersection&, const Scene&) const;

};

#endif