
#include "Ray.h"

Ray::Ray() {
    this->point = Vector(0, 0, 0);
    this->direction = Vector(0, 0, 1);
}

Ray::Ray(Vector p, Vector d) {
    this->point = p;
    this->direction = d;
}