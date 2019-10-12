
#ifndef AMBIENT_LIGHT_H_
#define AMBIENT_LIGHT_H_

#include "Light.h"

class AmbientLight : public Light {

public:
    AmbientLight();
    AmbientLight(Vector c);

    Vector LightShading(const Intersection&, const Scene&) const;
    bool Intersect(const Intersection&, const Scene&) const  { return false; }

};

#endif