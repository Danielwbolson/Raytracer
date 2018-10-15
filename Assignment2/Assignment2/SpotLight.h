
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

    Vector Position() { return position; }
    Vector Direction() { return direction; }
    float Theta() { return theta; }
    float Phi() { return phi; }

    Vector LightShading(Intersection*, Scene*);
    bool Intersect(Intersection*, Scene*);

};

#endif