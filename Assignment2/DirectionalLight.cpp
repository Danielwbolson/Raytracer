
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() {

}

DirectionalLight::DirectionalLight(Vector c, Vector d) {
    this->color = c;
    this->direction = d;
}

Vector DirectionalLight::LightShading(const Intersection& i, const Scene& s) const {
    if (Intersect(i, s))
        return Vector(0, 0, 0);

    Camera c = s.camera;

    Vector view = (c.Position() - i.point).Normalize();
    Vector light = -direction;

    Vector reflect = light.Reflection(i.normal);

    Vector intensity = color;
    Vector diffuse = i.material.Diffuse() * (i.normal.Dot(light));
    Vector specular = i.material.Specular() * (float)pow(view.Dot(reflect), i.material.Exponent());

    return intensity * (diffuse + specular);
}

bool DirectionalLight::Intersect(const Intersection& inter, const Scene& s) const {
    for (int i = 0; i < s.surfaces.size(); i++) {
        Ray r = Ray(inter.point + inter.normal * 0.0001f, (-direction).Normalize());

        if (s.surfaces[i]->Shadow(r)) {
            return true;
        }
    }

    return false;
}