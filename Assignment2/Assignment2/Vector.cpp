
#include "Vector.h"

// Constructors and Destructors

Vector::Vector() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector::Vector(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::~Vector() {

}


// Operators

Vector Vector::operator+(const Vector& v) const {
    return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(const Vector& v) const {
    return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator+=(const Vector& v) {
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

Vector Vector::operator-=(const Vector& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

Vector Vector::operator*(const float f) const {
    return Vector(x * f, y * f, z * f);
}
Vector operator*(const float f, const Vector& v) {
    return v * f;
}

Vector Vector::operator*(const int i) const {
    return Vector(x * i, y * i, z * i);
}
Vector operator*(const int i, const Vector& v) {
    return v * i;
}

Vector Vector::operator*(const Vector v) const {
    return Vector(x * v.x, y * v.y, z * v.z);
}

Vector Vector::operator/(const float f) const {
    return Vector(x / f, y / f, z / f);
}

Vector Vector::operator-() {
    return Vector(-x, -y, -z);
}


// Vector Functions

float Vector::Dot(const Vector& v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vector Vector::Cross(const Vector& v) const {
    return
        Vector(y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x);
}

float Vector::Length() const {
    return sqrt(Dot(*this));
}

float Vector::AngleBetween(const Vector& v, bool degrees) const {
    float angle = acos((Dot(v)) / (Length() * v.Length()));

    if (degrees)
        angle *= 180.0f / M_PI;

    return angle;
}

Vector Vector::Normalize() const {
    return Vector(x / Length(), y / Length(), z / Length());
}

Vector Vector::Reflection(const Vector& n) const {
    return 2 * (Dot(n)) * n - *(this);
}

double Vector::Distance(const Vector& v) const {
    return sqrt(pow(x - v.x, 2) + pow(y - v.y, 2) + pow(z - v.z, 2));
}