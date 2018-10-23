
#ifndef VECTOR_H_
#define VECTOR_H_

#define _USE_MATH_DEFINES
#include <math.h>

class Vector {

public:
    Vector();
    Vector(float x, float y, float z);
    ~Vector();

    float x, y, z;

    // Operators
    Vector operator+(const Vector&) const;
    Vector operator-(const Vector&) const;
    Vector operator+=(const Vector&);
    Vector operator-=(const Vector&);
    Vector operator*(const float) const;
    Vector operator*(const int) const;
    Vector operator*(const Vector&) const;
    Vector operator/(const float) const;
    Vector operator-() const;
    Vector operator=(const Vector&);

    // Vector functions
    float Dot(const Vector&) const;
    Vector Cross(const Vector&) const;
    float Length() const;
    float AngleBetween(const Vector&, bool degrees = false) const;
    Vector Normalize() const;
    Vector Reflection(const Vector&) const;
    double Distance(const Vector&) const;
};

Vector operator*(const int, const Vector&);
Vector operator*(const float, const Vector&);

#endif