
#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(Vector p, Vector d, Vector u, float a) {
    this->position = p;
    this->direction = d;
    this->up = u;
    this->vert_halfAngle = a / 180.0 * M_PI;
}

void Camera::Setup(int w, int h) {
    right = up.Cross(direction).Normalize();

    halfHeight = tan(vert_halfAngle);
    halfWidth = ((float)w / (float)h) * halfHeight;

    topLeft = position + direction + halfHeight * up - halfWidth * right;

    pixel_width = (2 * halfHeight) / (float)h;
}