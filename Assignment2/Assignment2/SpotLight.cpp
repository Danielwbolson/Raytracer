
#include "SpotLight.h"

SpotLight::SpotLight() {

}

SpotLight::SpotLight(Vector c, Vector p, Vector d, float theta, float phi) {
    this->color = c;
    this->position = p;
    this->direction = d;
    this->theta = theta;
    this->phi = phi;
}

Vector SpotLight::LightShading(Intersection* i, Scene* s) {
    return Vector(0, 0, 0);
}

bool SpotLight::Intersect(Intersection* inter, Scene* s) {
    for (int i = 0; i < s->surfaces.size(); i++) {
        Ray r = Ray(inter->point + inter->normal * 0.01f, (s->surfaces[i]->Position() - inter->point).Normalize());

        if (s->surfaces[i]->IsAnIntersection(&r)) {
            return true;
        }
    }
}