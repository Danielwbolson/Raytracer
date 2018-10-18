
#ifndef RAY_H_
#define RAY_H_

#include "Vector.h"

class Ray {
public:

    Ray();
    Ray(Vector, Vector);

    Ray operator=(const Ray&);

    Vector point;
    Vector direction;
};

#endif