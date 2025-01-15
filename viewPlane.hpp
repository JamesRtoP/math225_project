#ifndef VIEWPLANE_HPP
#define VIEWPLANE_HPP
#include "source.hpp"
#include "basic_geometry.hpp"

class viewPlane
{
private:
double width;
double height;
point cameraOrigin;
vector upDir;
vector depthDir;//distance from camera to viewPlane
vector widthDir;
double depth;

public:
viewPlane(void);


};





#endif