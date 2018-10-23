
#include "NormalTriangle.h"

NormalTriangle::NormalTriangle() {}

NormalTriangle::NormalTriangle(const Vector v1, const Vector v2, const Vector v3, 
    const Vector n1, const Vector n2, const Vector n3) {
    vertices = new Vector[3]{ v1, v2, v3 };
    normals = new Vector[3]{ n1, n2, n3 };

    position = (v1 + v2 + v3) / 3.0f;
}

/*
 * https://gamedev.stackexchange.com/questions/23743/whats-the-most-efficient-way-to-find-barycentric-coordinates
 */
bool NormalTriangle::IsAnIntersection(const Ray& r, Intersection& i) const {
    // plane intersection
    float t = (vertices[0] - r.point).Dot(normal) / (r.direction.Dot(normal));

    // behind us
    if (t < 0) return false;

    // triangle intersection
    Vector p = r.point + t * r.direction;

    float alpha, beta, gamma;
    Vector v0_1 = vertices[1] - vertices[0];
    Vector v0_2 = vertices[2] - vertices[0];
    Vector v0_p = p - vertices[0];

    float d00 = v0_1.Dot(v0_1);
    float d01 = v0_1.Dot(v0_2);
    float d11 = v0_2.Dot(v0_2);
    float d20 = v0_p.Dot(v0_1);
    float d21 = v0_p.Dot(v0_2);

    float invDenom = 1.0 / (d00 * d11 - d01 * d01);
    alpha = (d11 * d20 - d01 * d21) * invDenom; // normal 0
    beta = (d00 * d21 - d01 * d20) * invDenom; // normal 1

    if (alpha < 0 || alpha > 1) return false;
    if (beta < 0 || beta > 1) return false;
    if (alpha + beta > 1) return false;

    // In the triangle

    i.point = r.point + t * r.direction;
    i.material = material;

    gamma = 1.0 - alpha - beta; // normal 2
    Vector n = gamma * normals[0] + alpha * normals[1] + beta * normals[2];
    i.normal = n.Normalize();

    return true;
}

/*
 * https://gamedev.stackexchange.com/questions/23743/whats-the-most-efficient-way-to-find-barycentric-coordinates
 */
bool NormalTriangle::Shadow(const Ray& r) const {
    float d = -position.Dot(normal);
    float t = -(r.point.Dot(normal) + d) / (r.direction.Dot(normal));

    if (t < 0) return false;

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

void NormalTriangle::CalculateNormal(const Vector& c) {
    Vector cross = (vertices[0] - vertices[1]).Cross(vertices[2] - vertices[1]);
    Vector c_n = cross.Normalize();

    if (cross.Dot(c) < 0) 
        normal = c_n;
    else 
        normal = -c_n;
}