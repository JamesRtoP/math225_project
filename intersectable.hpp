#ifndef INTERSECTABLE_HPP
#define INTERSECTABLE_HPP

#include "source.hpp"
#include "basic_geometry.hpp"
#include "light.hpp"

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

class sphere : public intersectable
{
private:
	point center;
	double radius;

public:

	sphere();
	sphere(point origin, double newRadius);
	//asumes the vector start at 0,0 
	virtual double intersects(vector intersector);//returns -1 if no possitive intersection
	//we have the distance in main as well as the vector, use that to pass in a point
	virtual double lights(directionalLight lighting, point onCircle);
};


class intersectableNode//worry about the big 5 later, possibly not necisarry
{
private:
	intersectable* object;
	intersectableNode* pNext;
protected:
public:
	intersectableNode(void);//copy constructor
	~intersectableNode(void);//destructor
	//copy constructor
	intersectableNode(intersectableNode& copyMe);//hardcopy of object, points to same location
	//move constructor
	intersectableNode(intersectableNode&& moveMe);
	//copy assignment operator
	intersectableNode& operator= (intersectableNode & copyMe);//hardcopy
	//move assignment operator
	intersectableNode& operator= (intersectableNode&& moveMe);
	intersectable* getObject(void);
	void setObject(intersectable* newObject);
	intersectableNode* getPNext(void);
	void setPNext(intersectableNode* newPNext);
};


class intersectableList
{
private:
	intersectableNode* pHead;
	bool isEmpty(void);
public:
	intersectableList(void);
	~intersectableList(void);
	void empty(void);
	void insertAtFront(intersectable* newObject);
	void removeAtFront(void);
	intersectable* intersects(vector v, double& closestIntersection);
	void unlinkObjects(void);//should only be used for the displayList (ie a senario where the object is linked elsewhere
};




#endif