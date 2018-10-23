
#include "Triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(const Vector v1, const Vector v2, Vector v3) {
    vertices = new Vector[3]{ v1, v2, v3 };

    position = (v1 + v2 + v3) / 3.0f;
}

/*
 * https://gamedev.stackexchange.com/questions/23743/whats-the-most-efficient-way-to-find-barycentric-coordinates
 */
bool Triangle::IsAnIntersection(const Ray& r, Intersection& i) const {
    float t = (position - r.point).Dot(normal) / (r.direction.Dot(normal));

    // t == 0 will never happen with floating point numbers

    // behind us
    if (t < 0) return false;

    // triangle intersection
    Vector p = r.point + t * r.direction;

    float alpha, beta;
    Vector v01 = vertices[1] - vertices[0];
    Vector v02 = vertices[2] - vertices[0];
    Vector v0p = p - vertices[0];

    float d00 = v01.Dot(v01);
    float d01 = v01.Dot(v02);
    float d11 = v02.Dot(v02);
    float d20 = v0p.Dot(v01);
    float d21 = v0p.Dot(v02);

    float invDenom = 1.0 / (d00 * d11 - d01 * d01);
    alpha = (d11 * d20 - d01 * d21) * invDenom;
    beta = (d00 * d21 - d01 * d20) * invDenom;

    if (alpha < 0 || alpha > 1) return false;
    if (beta < 0 || beta > 1) return false;
    if (alpha + beta > 1) return false;

    i.point = r.point + t * r.direction;
    i.material = material;
    i.normal = normal;

    return true;
}

/*
 * https://gamedev.stackexchange.com/questions/23743/whats-the-most-efficient-way-to-find-barycentric-coordinates
 */
bool Triangle::Shadow(const Ray& r) const {

    // plane intersection
    float t = (vertices[0] - r.point).Dot(normal) / (r.direction.Dot(normal));

    if (t < 0) return false;

    // triangle intersection
    Vector p = r.point + t * r.direction;

    float alpha, beta;
    Vector v01 = vertices[1] - vertices[0];
    Vector v02 = vertices[2] - vertices[0];
    Vector v0p = p - vertices[0];

    float d00 = v01.Dot(v01);
    float d01 = v01.Dot(v02);
    float d11 = v02.Dot(v02);
    float d20 = v0p.Dot(v01);
    float d21 = v0p.Dot(v02);

    float invDenom = 1.0 / (d00 * d11 - d01 * d01);
    alpha = (d11 * d20 - d01 * d21) * invDenom;
    beta = (d00 * d21 - d01 * d20) * invDenom;

    if (alpha < 0 || alpha > 1) return false;
    if (beta < 0 || beta > 1) return false;
    if (alpha + beta > 1) return false;

    return true;
}

void Triangle::CalculateNormal(const Vector& c) {
    Vector cross = (vertices[0] - vertices[1]).Cross(vertices[2] - vertices[1]);
    Vector c_n = cross.Normalize();

    if (cross.Dot(c) < 0)
        normal = c_n;
    else
        normal = -c_n;
}