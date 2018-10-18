
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
    Material material;

    Surface() {}
    Vector Position() const { return position; }
    virtual bool IsAnIntersection(const Ray&, Intersection&) const = 0;
    virtual bool Shadow(const Ray&) const = 0;
};

#endif
