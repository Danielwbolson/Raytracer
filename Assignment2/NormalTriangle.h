
#ifndef NORMAL_TRIANGLE_H_
#define NORMAL_TRIANGLE_H_

#include "Surface.h"

class NormalTriangle : public Surface {

private:
    Vector* vertices;
    Vector* normals;
    Vector normal;

public:
    NormalTriangle();
    NormalTriangle(const Vector, const Vector, const Vector, const Vector, const Vector, const Vector);

    Vector* Vertices() const { return vertices; }
    Vector* Normals() const { return normals; }
    Vector Normal() const { return normal; }

    bool IsAnIntersection(const Ray&, Intersection&) const;
    bool Shadow(const Ray&) const;
    void CalculateNormal(const Vector&);

};

#endif