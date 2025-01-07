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


sphere::sphere()
{
	this->center = point(0,10,0);
	this->radius = 1;
	this->color = sf::Color(102,255,0);
	this->type = SPHERE;
}

sphere::sphere(point origin, double newRadius)
{
	this->center = origin;
	this->radius = newRadius;
	this->color = sf::Color(102,255,0);
	this->type = SPHERE;

}

//asumes the vector start at 0,0 
double sphere::intersects(vector intersector)//returns -1 if no possitive intersection
{
	//vector notation, co = from center to origin
	vector co = fromTwoPoints(this->center, point(0,0,0));
	double u2 = dotProduct(intersector, intersector);
	double udotco = dotProduct(intersector, co);
	double a = u2;
	double b = 2 * udotco;
	double c = dotProduct(co,co) - this->radius * this->radius;
	double insideRoot = insideTheRoot(a,b,c);
	if(insideRoot < 0)
	{
		return -1;
	}
	else if(insideRoot == 0)
	{
		return outsideTheRootPos(a,b,c,insideRoot);
	}
	else
	{
		double q1 = outsideTheRootPos(a,b,c,insideRoot);
		double q2 = outsideTheRootNeg(a,b,c,insideRoot);
		return std::min(q1,q2);
	}
}


//we have the distance in main as well as the vector, use that to pass in a point
double sphere::lights(directionalLight lighting, point onCircle)
{
	vector normalDir = fromTwoPoints(this->center, onCircle);
	vector normalUnit = makeUnitVector(normalDir);
	double top = dotProduct(lighting.getDir()*(-1), normalUnit);
	double bottom = getMagnitude(lighting.getDir()) + getMagnitude(normalUnit);
	return top/bottom;
}


intersectableNode::intersectableNode(void)//copy constructor
{
	object = NULL;
	pNext = NULL;
}
intersectableNode::~intersectableNode(void)//destructor
{
	std::cout << "NodeDestructor" << std::endl;
	if(object != NULL)
	{
		delete object;
	}
	/*
	if(pNext != NULL)
	{
		delete pNext;
	}
	*/
}
//copy constructor
intersectableNode::intersectableNode(intersectableNode& copyMe)//hardcopy of object, points to same location
{
	//cannont instantiate a new intersectable because intersctable is a pure virtual class
	//this->object = new intersectable(*(copyMe.object));
	this->pNext = copyMe.pNext;
}
//move constructor
intersectableNode::intersectableNode(intersectableNode&& moveMe)
{
	this->object = moveMe.object;
	moveMe.object = NULL;
	this->pNext = moveMe.pNext;
	moveMe.pNext = NULL;
}


//copy assignment operator
intersectableNode& intersectableNode::operator= (intersectableNode & copyMe)//hardcopy
{
	pNext = NULL;
	return *this;
}

//move assignment operator
intersectableNode& intersectableNode::operator= (intersectableNode&& moveMe)
{
	this->object = moveMe.object;
	moveMe.object = NULL;
	this->pNext = moveMe.pNext;
	moveMe.pNext = NULL;
	return *this;
}




intersectable* intersectableNode::getObject(void)
{
	return this->object;
}
void intersectableNode::setObject(intersectable* newObject)
{
	this->object = newObject;
}
intersectableNode* intersectableNode::getPNext(void)
{
	return this->pNext;
}
void intersectableNode::setPNext(intersectableNode* newPNext)
{
	this->pNext = newPNext;
}



bool intersectableList::isEmpty(void)
{
	
	if(this->pHead == NULL)
	{
		return true; 
	}
	return false;
}
intersectableList::intersectableList(void)
{
	this->pHead = NULL;
}
intersectableList::~intersectableList(void)
{
	std::cout << "ListDestructor" << std::endl;
	this->empty();
}
void intersectableList::empty(void)
{
	intersectableNode* pCur = this->pHead;
	intersectableNode* pDel = NULL;
	while(pCur != NULL)
	{
		pDel = pCur;
		pCur = pCur->getPNext();
		delete pDel;
	}
}
void intersectableList::insertAtFront(intersectable* newObject)
{
	intersectableNode* pNew = new intersectableNode();
	pNew->setObject(newObject);
	pNew->setPNext(this->pHead);
	this->pHead = pNew;
}
void intersectableList::removeAtFront(void)
{
	if(this->pHead != NULL)
	{
		intersectableNode* pDel = this->pHead;
		this->pHead = this->pHead->getPNext();	
		delete pDel;
	}
}
intersectable* intersectableList::intersects(vector v, double& closestIntersection)
{
	intersectableNode* pIntersect = NULL;
	intersectableNode* pCur= this->pHead;
	double newIntersection = -1;
	closestIntersection = -1;
	while(pCur != NULL)
	{
		newIntersection = pCur->getObject()->intersects(v);
		if(newIntersection > 0 && (newIntersection < closestIntersection || closestIntersection == -1))
		{
			closestIntersection = newIntersection;
			pIntersect = pCur;
		}
		pCur = pCur->getPNext();
	}
	if(closestIntersection < 0)
	{
		return NULL;
	}
	else
	{
		return pIntersect->getObject();
	}
}
void intersectableList::unlinkObjects(void)//should only be used for the displayList (ie a senario where the object is linked elsewhere
{
	intersectableNode* pCur = this->pHead;
	while(pCur != NULL)
	{
		pCur->setObject(NULL);
		pCur = pCur->getPNext();
	}
}