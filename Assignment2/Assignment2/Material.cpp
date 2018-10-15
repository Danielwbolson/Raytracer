
#include "Material.h"

Material::Material() {

}

Material::Material(Vector a, Vector d, Vector s, float e, Vector t, float i) {
    this->c_ambient = a;
    this->c_diffuse = d;
    this->c_specular = s;
    this->exponent = e;
    this->c_transmissive = t;
    this->index_of_refraction = i;
}