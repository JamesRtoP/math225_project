#include "viewPlane.hpp"

viewPlane::viewPlane(void)
{
    this->cameraOrigin = point(0,0,0);
    this->depth = 1;
    this->height = 10;
    this->width = 10;
    this->depthDir = vector(0,1,0);
    this->upDir = vector(0,0,1);
}

