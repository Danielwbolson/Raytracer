
#include "AmbientLight.h"

AmbientLight::AmbientLight() {

}

AmbientLight::AmbientLight(Vector c) {
    this->color = c;
}

Vector AmbientLight::LightShading(Intersection* i, Scene* s) {
    return color * i->material->Ambient() * 255;
}