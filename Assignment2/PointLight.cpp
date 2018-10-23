
#include "PointLight.h"

PointLight::PointLight() {

}

PointLight::PointLight(Vector c, Vector p) {
    this->color = c;
    this->position = p;
}

Vector PointLight::LightShading(const Intersection& i, const Scene& s) const {
    if (Intersect(i, s))
        return Vector(0, 0, 0);

    Vector view = (s.camera.Position() - i.point).Normalize();
    Vector light = (position - i.point).Normalize();

    Vector reflect = light.Reflection(i.normal);
    double dist = i.point.Distance(position);

    Vector intensity = color / pow(dist, 2);
    Vector diffuse = i.material.Diffuse() * (i.normal.Dot(light));
    Vector specular = i.material.Specular() * (float)pow(view.Dot(reflect), i.material.Exponent());

    return intensity * (diffuse + specular);
}

bool PointLight::Intersect(const Intersection& inter, const Scene& s) const {
    for (int i = 0; i < s.surfaces.size(); i++) {
        Vector p = inter.point + inter.normal * 0.0001f;
        Vector dir = (this->Position() - inter.point).Normalize();
        Ray r = Ray(p, dir);

        if (s.surfaces[i]->Shadow(r)) {
            return true;
        }
    }
    
    return false;
}