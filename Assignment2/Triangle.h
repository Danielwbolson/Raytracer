
#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Surface.h"

class Triangle {
private:
    int* vertices;
    Vector normalFront;
    Vector normalBack;

public:
    Triangle();
    Triangle(const int, const int, const int); // regular triangle
    Triangle(const int, const int, const int, const float, const float, const float); // normal triangle

    int* Vertices() const { return vertices; }
    Vector NormalFront() const { return normalFront; }
    Vector NormalBack() const { return normalBack; }

    bool IsAnIntersection(const Ray&, Intersection&) const;
    bool Shadow(const Ray&) const;

};

#endif