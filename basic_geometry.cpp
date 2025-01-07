#include "basic_geometry.hpp"

point::point()
{
    x=0;
    y=0;
    z=0;
}
point::point(double newX, double newY, double newZ)
{
    x = newX;
	y = newY;
	z = newZ;
}
double point::getx(void) const
{
    return x;
}
double point::gety(void) const
{
	return y;
}
double point::getz(void) const
{
    return z;
}

std::ostream& operator<< (std::ostream& stream, const point & aPoint)
{
	stream << "(" << aPoint.getx() <<"," << aPoint.gety() << "," << aPoint.getz() << ")";
	return stream;
}


vector::vector()
{

    this->xdir = 0;
    this->ydir = 0;
    this->zdir = 0;
}
vector::vector(double newXDir, double newYDir, double newZDir)
{
    this->xdir = newXDir;
    this->ydir = newYDir;
    this->zdir = newZDir;
}
double vector::getXDir(void) const
{
    return this->xdir;
}
double vector::getYDir(void) const
{
    return this->ydir;
}
double vector::getZDir(void) const
{
    return this->zdir;
}
void vector::setXDir(double newxdir)
{
    this->xdir = newxdir;
}
void vector::setYDir(double newydir)
{
    this->ydir = newydir;
}
void vector::setZDir(double newzdir)
{
    this->zdir = newzdir;
}
vector& vector::operator/(double divisor)
{
    this->xdir /= divisor;
    this->ydir /= divisor;
    this->zdir /= divisor;
    return *this;
}
vector& vector::operator*(double divisor)
{
    this->xdir *= divisor;
    this->ydir *= divisor;
    this->zdir *= divisor;
    return *this;
}

double dotProduct(vector one, vector two)
{
	return one.getXDir() * two.getXDir() +one.getYDir() * two.getYDir() + one.getZDir() * two.getZDir();	
}
double getMagnitude(vector v)
{
	return sqrt(dotProduct(v,v));
}
vector makeUnitVector(vector v)
{
	return v / getMagnitude(v);
}
point pointFromVector(vector v, double t)
{
	return point(v.getXDir()*t, v.getYDir()*t, v.getZDir()*t);
}
vector fromTwoPoints(point from, point to)
{
	vector returnVector;
	returnVector.setXDir(to.getx()-from.getx());
	returnVector.setYDir(to.gety()-from.gety());
	returnVector.setZDir(to.getz()-from.getz());
	return returnVector;
}

void ray::setT(double newT)
{
    this->t = newT;
}
void ray::setDir(vector newDir)
{
    this->dir = newDir;
}
void ray::setOrigin(point newOrigin)
{
    this->origin = newOrigin;
}
double ray::getT(void) const
{
    return this->t;
}
point ray::getOrigin(void)
{
    return this->origin;
}
vector ray::getDir(void)
{	
    return this->dir;
}

std::ostream& operator<< (std::ostream& stream, const vector & printMe)
{
	stream << "[" << printMe.getXDir() <<"," << printMe.getYDir() << "," << printMe.getZDir() << "]";
	return stream;
}





