
#include "AmbientLight.h"

AmbientLight::AmbientLight() {

}

AmbientLight::AmbientLight(Vector c) {
    this->color = c;
}

Vector AmbientLight::LightShading(const Intersection& i, const Scene& s) const {
    return color * i.material.Ambient();
}