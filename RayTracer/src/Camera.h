
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

    Camera operator=(const Camera&);

    Vector Position() const { return position; }
    Vector Direction() const { return direction; }
    Vector Up() const { return up; }
    Vector Right() const { return right; }
    Vector TopLeft() const { return topLeft; }

    float HalfHeight() const { return halfHeight; }
    float HalfWidth() const { return halfWidth; }
    float VertHalfAngle() const { return vert_halfAngle; }
    float PixelWidth() const { return pixel_width; }
};

#endif