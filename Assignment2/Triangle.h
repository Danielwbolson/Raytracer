
#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Surface.h"

class Triangle : public Surface {
private:
    Vector* vertices;
    Vector normalFront;
    Vector normalBack;

public:
    Triangle();
    Triangle(const Vector, const Vector, const Vector); // regular triangle

    Vector* Vertices() const { return vertices; }
    Vector NormalFront() const { return normalFront; }
    Vector NormalBack() const { return normalBack; }

    bool IsAnIntersection(const Ray&, Intersection&) const;
    bool Shadow(const Ray&) const;
    void CalculateNormal(const Vector&);

};

#endif