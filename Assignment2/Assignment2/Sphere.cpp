
#include "Sphere.h"

Sphere::Sphere(Vector v, float r) {
    this->position = v;
    this->radius = r;
}

bool Sphere::IsAnIntersection(Ray* r, Intersection* i) {

    // Initial check
    Vector L = position - r->point;
    if (L.Dot(r->direction) < 0)
        return false;

    // We have a chance of colliding
    float a = 1;
    float b = (2 * r->direction).Dot(r->point - position);
    float c = (r->point - position).Dot(r->point - position) - (radius * radius);
    
    float radical = b * b - 4 * a * c;
    if (radical < 0)
        return false;

    float sqrt_rad = sqrt(radical);
    float t1 = (-b + sqrt_rad) / (2 * a);
    float t2 = (-b - sqrt_rad) / (2 * a);

    float chosen_t = fmin(t1, t2);
    if (chosen_t < 0) {
        chosen_t = fmax(t1, t2);
        if (chosen_t < 0) {
            return false;
        }
    }

    if (i) {
        i->point = r->point + chosen_t * r->direction;
        i->material = material;
        i->normal = (i->point - position).Normalize();
    }

    return true;
}