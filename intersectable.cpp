#include "intersectable.hpp"

double intersectable::intersects(vector intersector)//pure virtual function
{
	return -2;
}
double intersectable::lights(ambientLight lighting)
{
	return lighting.getPower();
}
double intersectable::lights(directionalLight lighting)
{
	return lighting.getPower();
	
}
double intersectable::lights(directionalLight lighting, point disAPoint)
{
	return lighting.getPower();
}
sf::Color intersectable::getColor(void)
{
	return this->color;
}
void intersectable::setColor(sf::Color newColor)
{
	this->color = newColor;
}



plane::plane()
{
	this->a = 0;
			this->b = 0;
			this->c = 1;
			this->x = 0;
			this->y = 0;
			this->z = -5;
	this->color = sf::Color(155,118,83);
	this->type = PLANE;
}
plane::plane(double newA, double newB, double newC)//plane through 0,0,0
{
	this->a = newA;
	this->b = newB;
	this->c = newC;
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->color = sf::Color(155,118,83);
	this->type = PLANE;
}
plane::plane(double newY) //plane perpindicular to y with the newY being the offset
{
	this->y = newY;
}

double plane::getY(void)
{
	return this->y;
}


double plane::intersects(vector intersector)//returns -1 if no possitive intersection
{
	vector normalV(this->a, this->b, this->c);
	double top = dotProduct(fromTwoPoints(point(0,0,0), point(x,y,z)),normalV);
	double bottom = dotProduct(intersector,normalV);
	if(bottom == 0)
	{
		return -1;
	}
	else
	{
		return top/bottom;
	}
}



restrictedPlane::restrictedPlane():plane(1)
{
	this->width = 10;
	this->height = 10;
	this->pixelWidth = 720;
	this->pixelHeight = 720;
}
restrictedPlane::restrictedPlane(double newWidth, double newHeight,double newA, double newB, double newC):plane(newA,newB,newC)
{
	this->width = newWidth;
	this->height = newHeight;
}

restrictedPlane::restrictedPlane(double newWidth, double newHeight, int newPixelWidth, int newPixelHeight, double newA, double newB, double newC):plane(newA,newB,newC)
	{
			this->width = newWidth;
			this->height = newHeight;
	this->pixelWidth = newPixelWidth;
	this->pixelHeight = newPixelHeight;
	}

point restrictedPlane::calculatePointFromPixel(int pixelnum)//only works with a plane perpindicular to the y-axis(i.e. y= 10) 
{//rows first, then columns
	int pixelColumn = pixelnum%this->pixelWidth;
	int pixelRow = pixelnum/this->pixelWidth;

	//next two are pixel's relative to 0,0,0 being the center of the plane
	double pixelPositionCol = pixelColumn - pixelWidth/2;
	double pixelPositionRow = pixelHeight/2 - pixelRow;//subrtracting because o row is poisitive 50 
	//percent relative to 0,0,0 with negative values being to the right
	double percentCol = pixelPositionCol/(pixelWidth/2);
	double percentRow = pixelPositionRow/(pixelHeight/2);
	
	double unitsInCol = percentCol*this->width/2;
	double unitsInRow = percentRow*this->height/2;

	point w (unitsInCol, this->getY(), unitsInRow);
	return w;	
}