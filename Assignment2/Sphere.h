
#ifndef SPHERE_H_
#define SPHERE_H_

#include "Surface.h"
#include "Vector.h"
#include "Intersection.h"
#include <stdio.h>

class Sphere : public Surface {

private:
    float radius;

public:
    Sphere(Vector, float);
    float Radius() const { return radius; }

    bool IsAnIntersection(const Ray&, Intersection&) const override;
    bool Shadow(const Ray&, const float) const override;
};

#endif