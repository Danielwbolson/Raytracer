
#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Vector.h"

class Material {
private:
    Vector c_ambient, c_diffuse, c_specular, c_transmissive;
    float exponent;
    float index_of_refraction;

public:
    Material();
    Material(Vector, Vector, Vector, float, Vector, float);

    Vector Ambient() { return c_ambient; }
    Vector Diffuse() { return c_diffuse; }
    Vector Specular() { return c_specular; }
    Vector Transmissive() { return c_transmissive; }

    float Exponent() { return exponent; }
    float IofR() { return index_of_refraction; }

};

#endif