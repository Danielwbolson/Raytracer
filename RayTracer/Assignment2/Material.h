
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

    Vector Ambient() const { return c_ambient; }
    Vector Diffuse() const { return c_diffuse; }
    Vector Specular() const { return c_specular; }
    Vector Transmissive() const { return c_transmissive; }

    float Exponent() const { return exponent; }
    float IofR() const { return index_of_refraction; }

    Material operator=(const Material&);
};

#endif