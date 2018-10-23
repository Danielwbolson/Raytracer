
#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Surface.h"

class Triangle : public Surface {
private:
    Vector* vertices;
    Vector normal;

public:
    Triangle();
    Triangle(const Vector, const Vector, const Vector); // regular triangle

    Vector* Vertices() const { return vertices; }
    Vector Normal() const { return normal; }

    bool IsAnIntersection(const Ray&, Intersection&) const;
    bool Shadow(const Ray&) const;
    void CalculateNormal(const Vector&);

};

#endif