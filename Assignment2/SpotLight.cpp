
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

Vector SpotLight::LightShading(const Intersection& i, const Scene& s) const {
    return Vector(0, 0, 0);
}

bool SpotLight::Intersect(const Intersection& inter, const Scene& s) const {
    for (int i = 0; i < s.surfaces.size(); i++) {
        Ray r = Ray(inter.point + inter.normal * 0.0001f, (s.surfaces[i]->Position() - inter.point).Normalize());

        if (s.surfaces[i]->Shadow(r)) {
            return true;
        }
    }
    return false;
}