
#ifndef DIRECTIONAL_LIGHT_H_
#define DIRECTIONAL_LIGHT_H_

#include "Light.h"

class DirectionalLight : public Light {
private:
    Vector direction;

public:
    DirectionalLight();
    DirectionalLight(Vector, Vector);

    Vector Direction() { return direction; }

    Vector LightShading(Intersection*, Scene*);
    bool Intersect(Intersection*, Scene*);

};

#endif