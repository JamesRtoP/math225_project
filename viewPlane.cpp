#include "viewPlane.hpp"

viewPlane::viewPlane(void)
{
    this->cameraOrigin = point(0,0,0);
    this->depth = 1;
    this->height = 10;
    this->width = 10;
    this->depthDir = vector(0,1,0);
    this->upDir = vector(0,0,1);
    this->widthDir = crossProduct(this->upDir, this->depthDir);//should point right
    this->moveDist = 1;
    this->rotateAngle = 15;
}

void viewPlane::moveLeft(void) // move in the negative widthDirection
{
    this->cameraOrigin = this->cameraOrigin - (makeUnitVector(this->widthDir) * this->moveDist);
}
void viewPlane::moveRight(void)
{
    this->cameraOrigin = this->cameraOrigin + (makeUnitVector(this->widthDir) * this->moveDist);
}
void viewPlane::moveUp(void)
{
    this->cameraOrigin = this->cameraOrigin + (makeUnitVector(this->upDir) * this->moveDist);

}
void viewPlane::moveDown(void)
{
    this->cameraOrigin = this->cameraOrigin - (makeUnitVector(this->upDir) * this->moveDist);

}
void viewPlane::moveForward(void)
{
    this->cameraOrigin = this->cameraOrigin + (makeUnitVector(this->depthDir) * this->moveDist);

}
void viewPlane::moveBack(void)
{
    this->cameraOrigin = this->cameraOrigin - (makeUnitVector(this->depthDir) * this->moveDist);

}

void viewPlane::rollRight(void)
{

}//rotate right
void viewPlane::rollLeft(void)
{

} //rotate left
void viewPlane::pitchUp(void)
{

} //look upwards
void viewPlane::pitchDown(void)
{

}//look downwards
void viewPlane::yawLeft(void)
{

}//turn left
void viewPlane::yarRight(void)
{

}//turn Right