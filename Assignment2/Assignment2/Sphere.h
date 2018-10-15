
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

    Vector Position() { return position; }
    float Radius() { return radius; }
    bool IsAnIntersection(Ray*, Intersection* = nullptr);

};

#endif