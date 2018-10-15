
#ifndef AMBIENT_LIGHT_H_
#define AMBIENT_LIGHT_H_

#include "Light.h"

class AmbientLight : public Light {

public:
    AmbientLight();
    AmbientLight(Vector c);

    Vector LightShading(Intersection*, Scene*);
    bool Intersect(Intersection*, Scene*) { return false; }

};

#endif