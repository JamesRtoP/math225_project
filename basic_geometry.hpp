#ifndef BASIC_GEOMETRY_HPP
#define BASIC_GEOMETRY_HPP

#include "source.hpp"

class point
{
private:
	double x;
	double y;
	double z;
public:
	point();
	point(double newX, double newY, double newZ);
	double getx(void) const;
	double gety(void) const;
	double getz(void) const;
};
std::ostream& operator<< (std::ostream& stream, const point & aPoint);

class vector
{
private:
	double xdir;
	double ydir;
	double zdir;
public:
	vector();
	vector(double newXDir, double newYDir, double newZDir);
	double getXDir(void) const;
	double getYDir(void) const;
	double getZDir(void) const;
	void setXDir(double newxdir);
	void setYDir(double newydir);
	void setZDir(double newzdir);

	vector& operator/(double divisor);
	vector& operator*(double divisor);
};

double dotProduct(vector one, vector two);
double getMagnitude(vector v);
vector makeUnitVector(vector v);
point pointFromVector(vector v, double t);
vector fromTwoPoints(point from, point to);

class ray
{
private:
	vector dir;
	point origin;
	//x,y,z for start point
	double t;//length of vector ie t[x,z,y]
public:
	void setT(double newT);
	void setDir(vector newDir);
	void setOrigin(point newOrigin);
	double getT(void) const;
	point getOrigin(void);
	vector getDir(void);
};
std::ostream& operator<< (std::ostream& stream, const vector & printMe);

#endif