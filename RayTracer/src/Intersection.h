
#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "Vector.h"
#include "Material.h"

struct Intersection {
    Vector point;
    Vector normal;
    Material material;

    Intersection operator=(const Intersection& i) {
        if (this == &i) return *this;

        this->point = i.point;
        this->normal = i.normal;
        this->material = i.material;
        return *this;
    }
};

#endif