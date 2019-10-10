
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

Material Material::operator=(const Material& m) {
    if (this == &m) return *this;

    this->c_ambient = m.Ambient();
    this->c_diffuse = m.Diffuse();
    this->c_specular = m.Specular();
    this->exponent = m.Exponent();
    this->c_transmissive = m.Transmissive();
    this->index_of_refraction = m.IofR();
}