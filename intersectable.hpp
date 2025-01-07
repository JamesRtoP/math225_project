#include "source.hpp"
#include "basic_geometry.hpp"
#include "light.hpp"

#ifndef INTERSECTABLE_HPP
#define INTERSECTABLE_HPP

enum Type
{
	SPHERE, PLANE, RESTRICTEDPLANE

};

class intersectable
{
private:
protected:
	sf::Color color;
	Type type;
public:
	virtual double intersects(vector intersector);//pure virtual function

	virtual double lights(ambientLight lighting);
	virtual double lights(directionalLight lighting);
	virtual double lights(directionalLight lighting, point disAPoint);
	sf::Color getColor(void);
	void setColor(sf::Color newColor);
};

class plane : public intersectable//restricted plane //using equation a(x-x1)+b(y-y1)+c(z-z1) = 0
{
private:
	//directional offsets
	//also where the plane is "centered" for view port
	double x;
	double y;
	double z;

	double a;
	double b;
	double c;

public:
	plane();
	plane(double newA, double newB, double newC);//plane through 0,0,0
	plane(double newY); //plane perpindicular to y with the newY being the offset
	double getY(void);
	virtual double intersects(vector intersector);//returns -1 if no possitive intersection
};

class restrictedPlane:plane
{
private:
	double width;
	double height;
	int pixelWidth;
	int pixelHeight;
public:
	restrictedPlane();
	restrictedPlane(double newWidth, double newHeight,double newA, double newB, double newC);
	restrictedPlane(double newWidth, double newHeight, int newPixelWidth, int newPixelHeight, double newA, double newB, double newC);
	point calculatePointFromPixel(int pixelnum);//only works with a plane perpindicular to the y-axis(i.e. y= 10) 
};

#endif