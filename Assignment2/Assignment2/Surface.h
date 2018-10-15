
#ifndef SURFACE_H_
#define SURFACE_H_

#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Material.h"

class Surface {
protected:
    Vector position;
public:
    Material* material;

    Surface() {}
    Vector Position() { return position; }
    virtual bool IsAnIntersection(Ray*, Intersection* = nullptr) = 0;
};

#endif
