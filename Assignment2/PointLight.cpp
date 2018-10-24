
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

    if (i.normal.Dot(light) < 0) return Vector(0, 0, 0);

    Vector reflect = light.Reflection(i.normal);
    double dist = i.point.Distance(position);

    Vector intensity = color / (dist * dist);
    Vector diffuse = i.material.Diffuse() * (float)(fmax(0, i.normal.Dot(light)));
    Vector specular = i.material.Specular() * (float)pow(fmax(0, view.Dot(reflect)), i.material.Exponent());

    return intensity * (diffuse + specular);
}

bool PointLight::Intersect(const Intersection& inter, const Scene& s) const {
    Vector p = inter.point + inter.normal * 0.0001f;
    Vector dir = (position - inter.point).Normalize();
    Ray r = Ray(p, dir);
    float dist = (position - inter.point).Length();

    for (int i = 0; i < s.surfaces.size(); i++) {
        if (s.surfaces[i]->Shadow(r, dist)) {
            return true;
        }
    }
    
    return false;
}