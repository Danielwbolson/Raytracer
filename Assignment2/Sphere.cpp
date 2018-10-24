
#include "Sphere.h"

Sphere::Sphere(Vector v, float r) {
    this->position = v;
    this->radius = r;
}

bool Sphere::IsAnIntersection(const Ray& r, Intersection& i) const {

    Vector toSurf = position - r.point;
    Vector dir = r.direction;

    // Initial check if surface is behind ray
    if (toSurf.Dot(dir) < 0)
        return false;

    // We have a chance of colliding
    Vector fromSurface = -toSurf;
    float a = 1;
    float b = (2 * dir).Dot(fromSurface);
    float c = (fromSurface).Dot(fromSurface) - (radius * radius);

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

    i.point = r.point + chosen_t * r.direction;
    i.material = material;
    i.normal = (i.point - position).Normalize();

    return true;
}

bool Sphere::Shadow(const Ray& r, const float dist) const {
    Vector toSurf = position - r.point;
    Vector dir = r.direction;

    // Initial check if surface is behind ray
    if (toSurf.Dot(dir) < 0)
        return false;

    // We have a chance of colliding
    Vector fromSurface = -toSurf;
    float a = 1;
    float b = (2 * dir).Dot(fromSurface);
    float c = (fromSurface).Dot(fromSurface) - (radius * radius);

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

    if (chosen_t > dist) return false;

    return true;
}