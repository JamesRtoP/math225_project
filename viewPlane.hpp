#ifndef VIEWPLANE_HPP
#define VIEWPLANE_HPP
#include "source.hpp"
#include "basic_geometry.hpp"

class viewPlane
{
private:
double width;
double height;
double depth;

point cameraOrigin;//point at which the camera rests and send rays to the viewplane

//all 3 vectors should be orthoginal
vector upDir;//dir directly up from camera origin
vector depthDir;//dir from camera to viewPlane
vector widthDir;//dir right off cameraOrigin

double moveDist;//the distance that the camera origin will move when it moves
double rotateAngle;//the angle the camera will rotate for roll,pitch, and yaw [0,180]


public:
viewPlane(void);

void moveLeft(void);
void moveRight(void);
void moveUp(void);
void moveDown(void);
void moveForward(void);
void moveBack(void);

void rollRight(void);//rotate right
void rollLeft(void); //rotate left
void pitchUp(void); //look upwards
void pitchDown(void);//look downwards
void yawLeft(void);//turn left
void yarRight(void);//turn Right
};





#endif