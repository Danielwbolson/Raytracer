
#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector.h"
#include <stdio.h>

class Camera {

private:
    Vector position;
    Vector direction;
    Vector up, right;

    Vector topLeft;

    float vert_halfAngle;
    float halfHeight, halfWidth;
    float pixel_width;
public:
    Camera();
    Camera(Vector, Vector, Vector, float);
    void Setup(int w, int h);

    Vector Position() { return position; }
    Vector Direction() { return direction; }
    Vector Up() { return up; }
    Vector Right() { return right; }
    Vector TopLeft() { return topLeft; }

    float HalfHeight() { return halfHeight; }
    float HalfWidth() { return halfWidth; }
    float VertHalfAngle() { return vert_halfAngle; }
    float PixelWidth() { return pixel_width; }
};

#endif