
#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "Vector.h"
#include "Material.h"

struct Intersection {
    Vector point;
    Vector normal;
    Material* material;
};

#endif