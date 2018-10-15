
#include "PointLight.h"

PointLight::PointLight() {

}

PointLight::PointLight(Vector c, Vector p) {
    this->color = c;
    this->position = p;
}

Vector PointLight::LightShading(Intersection* i, Scene* s) {
    if (Intersect(i, s))
        return Vector(0, 0, 0);

    Vector view = (s->camera->Position() - i->point).Normalize();
    Vector light = (position - i->point).Normalize();

    Vector reflect = light.Reflection(i->normal);
    double dist = i->point.Distance(position);

    Vector intensity = color / pow(dist, 2);
    Vector diffuse = i->material->Diffuse() * (i->normal.Dot(light));
    Vector specular = i->material->Specular() * (float)pow(view.Dot(reflect), i->material->Exponent());

    return intensity * (diffuse + specular) * 255;
}

bool PointLight::Intersect(Intersection* inter, Scene* s) {
    for (int i = 0; i < s->surfaces.size(); i++) {
        Ray r = Ray(inter->point + inter->normal * 0.0001f, (this->Position() - inter->point).Normalize());

        if (s->surfaces[i]->IsAnIntersection(&r)) {
            return true;
        }
    }
    
    return false;
}