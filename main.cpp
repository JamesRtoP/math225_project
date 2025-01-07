#include "source.hpp"
#include "basic_geometry.hpp"

enum lightType
{
	AMBIENT, DIRECTIONAL, POINT
};

class light
{
private:
protected:
	double power;
	lightType type;
	sf::Color color;
public:
	double getPower(void)
	{
		return this->power;
	}	
	
	void setPower(double newPower)
	{
		this->power = newPower;
	}

	lightType getType(void)
	{
		return this->type;
	}

	light(double newPower, lightType newType)
	{
		this->power = newPower;
		this->type = newType;
		this->color = sf::Color::White;
	}
};

class ambientLight : public light
{
private:
protected:
public:
	ambientLight(double newPower):light(newPower, AMBIENT)
	{
	}
	
};

class directionalLight : public light
{
private:
	vector dir;
protected:
public:
	vector getDir (void)
	{
		return this->dir;
	}

	void setDir(vector newDir)
	{
		this->dir = newDir;
	}
	directionalLight(double newPower,vector newDir):light(newPower, DIRECTIONAL)
	{
		this->dir = newDir;
	}

};

vector fromTwoPoints(point from, point to)
{
	vector returnVector;
	returnVector.setXDir(to.getx()-from.getx());
	returnVector.setYDir(to.gety()-from.gety());
	returnVector.setZDir(to.getz()-from.getz());
	return returnVector;
}
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
	virtual double intersects(vector intersector)//pure virtual function
	{
		return -2;
	}
	virtual double lights(ambientLight lighting)
	{
		return lighting.getPower();
	}
	virtual double lights(directionalLight lighting)
	{
		return lighting.getPower();
		
	}
	virtual double lights(directionalLight lighting, point disAPoint)
	{
		return lighting.getPower();
	}
	sf::Color getColor(void)
	{
		return this->color;
	}
	void setColor(sf::Color newColor)
	{
		this->color = newColor;
	}
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
	plane()
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
	plane(double newA, double newB, double newC)//plane through 0,0,0
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
	plane(double newY) //plane perpindicular to y with the newY being the offset
	{
		this->y = newY;
	}
	
	double getY(void)
	{
		return this->y;
	}


	virtual double intersects(vector intersector)//returns -1 if no possitive intersection
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


};

class restrictedPlane:plane
{
private:
	double width;
	double height;
	int pixelWidth;
	int pixelHeight;
public:
	restrictedPlane():plane(1)
	{
		this->width = 10;
		this->height = 10;
		this->pixelWidth = 720;
		this->pixelHeight = 720;
	}
	restrictedPlane(double newWidth, double newHeight,double newA, double newB, double newC):plane(newA,newB,newC)
	{
		this->width = newWidth;
		this->height = newHeight;
	}

	restrictedPlane(double newWidth, double newHeight, int newPixelWidth, int newPixelHeight, double newA, double newB, double newC):plane(newA,newB,newC)
        {
                this->width = newWidth;
                this->height = newHeight;
		this->pixelWidth = newPixelWidth;
		this->pixelHeight = newPixelHeight;
        }

	point calculatePointFromPixel(int pixelnum)//only works with a plane perpindicular to the y-axis(i.e. y= 10) 
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
};





//these functions are both for the quadratic formula
double outsideTheRootPos(double a, double b, double c, double insideRoot)
{
	return (-1 * b + sqrt(insideRoot))/(2*a);

}

double outsideTheRootNeg(double a, double b, double c, double insideRoot)
{
	return (-1 * b + sqrt(insideRoot))/(2*a);

}

double insideTheRoot(double a, double b, double c)
{
	return b*b-4*a*c;
}

class sphere : public intersectable
{
private:
	point center;
	double radius;

public:


	sphere()
	{
		this->center = point(0,10,0);
		this->radius = 1;
		this->color = sf::Color(102,255,0);
		this->type = SPHERE;
	}

	sphere(point origin, double newRadius)
	{
		this->center = origin;
		this->radius = newRadius;
		this->color = sf::Color(102,255,0);
		this->type = SPHERE;

	}

	//asumes the vector start at 0,0 
	virtual double intersects(vector intersector)//returns -1 if no possitive intersection
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
	virtual double lights(directionalLight lighting, point onCircle)
	{
		vector normalDir = fromTwoPoints(this->center, onCircle);
		vector normalUnit = makeUnitVector(normalDir);
		double top = dotProduct(lighting.getDir()*(-1), normalUnit);
		double bottom = getMagnitude(lighting.getDir()) + getMagnitude(normalUnit);
		return top/bottom;
	}
	/*
	virtual double lights(ambientLight lighting)
	{
		return lighting.getPower();
	}
	*/
};


class intersectableNode//worry about the big 5 later, possibly not necisarry
{
private:
	intersectable* object;
	intersectableNode* pNext;
protected:
public:
	intersectableNode(void)//copy constructor
	{
		object = NULL;
		pNext = NULL;
	}
	~intersectableNode(void)//destructor
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
	intersectableNode(intersectableNode& copyMe)//hardcopy of object, points to same location
	{
		//cannont instantiate a new intersectable because intersctable is a pure virtual class
		//this->object = new intersectable(*(copyMe.object));
		this->pNext = copyMe.pNext;
	}
	//move constructor
	intersectableNode(intersectableNode&& moveMe)
	{
		this->object = moveMe.object;
		moveMe.object = NULL;
		this->pNext = moveMe.pNext;
		moveMe.pNext = NULL;
	}


	//copy assignment operator
	intersectableNode& operator= (intersectableNode & copyMe)//hardcopy
	{
                pNext = NULL;
		return *this;
	}

	//move assignment operator
	intersectableNode& operator= (intersectableNode&& moveMe)
	{
		this->object = moveMe.object;
                moveMe.object = NULL;
                this->pNext = moveMe.pNext;
                moveMe.pNext = NULL;
		return *this;
	}
	



	intersectable* getObject(void)
	{
		return this->object;
	}
	void setObject(intersectable* newObject)
	{
		this->object = newObject;
	}
	intersectableNode* getPNext(void)
	{
		return this->pNext;
	}
	void setPNext(intersectableNode* newPNext)
	{
		this->pNext = newPNext;
	}
};


class intersectableList
{
private:
	intersectableNode* pHead;
	bool isEmpty(void)
	{
		
		if(this->pHead == NULL)
		{
			return true; 
		}
		return false;
	}
public:
	intersectableList(void)
	{
		this->pHead = NULL;
	}
	~intersectableList(void)
	{
		std::cout << "ListDestructor" << std::endl;
		this->empty();
	}
	void empty(void)
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
	void insertAtFront(intersectable* newObject)
	{
		intersectableNode* pNew = new intersectableNode();
		pNew->setObject(newObject);
		pNew->setPNext(this->pHead);
		this->pHead = pNew;
	}
	void removeAtFront(void)
	{
		if(this->pHead != NULL)
		{
			intersectableNode* pDel = this->pHead;
			this->pHead = this->pHead->getPNext();	
			delete pDel;
		}
	}
	intersectable* intersects(vector v, double& closestIntersection)
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
	void unlinkObjects(void)//should only be used for the displayList (ie a senario where the object is linked elsewhere
	{
		intersectableNode* pCur = this->pHead;
		while(pCur != NULL)
		{
			pCur->setObject(NULL);
			pCur = pCur->getPNext();
		}
	}


	
};


class one
{
private:
	int x;
public:
	one()
	{
		x = 13;
	}
};

class two : one
{
public:
	int y;
	two() : one()
	{
		y = 45;
	}


};

double quadraticFormulaUnsafePositiveRoot(double a, double b, double c)//no check for negative sqrt
{
	double root = sqrt(b*b-4*a*c);
	return (0-b+root)/2*a;
}

double quadraticFormulaUnsafeNegativeRoot(double a, double b, double c)//no check for negative sqrt
{
	double root = sqrt(b*b-4*a*c);
	return (0-b-root)/2*a;
}



//I could make it a hash table, that would be pretty fire
//hash by node type
int main(void)
{
	int render_width = 720;
        int render_height = render_width;
        int& rh = render_height;
        int& rw = render_width;

	sf::RenderWindow window(sf::VideoMode(rw,rh), "View Port");

	sf::Image screen;
	screen.loadFromFile("assets/orangy_1000x1000.png");

	sf::Texture screen_t;
	screen_t.create(rw,rh);
	
	sf::Uint8* pixels = new sf::Uint8[rw*rh*4];
	ambientLight l1(0.5);
	directionalLight l2(0.5, vector(0,0,-1));	
	point origin(0,0,0);

	intersectable* objects;
	restrictedPlane viewPlane;//: = new restrictedPlane();
	//plane floor;
	intersectableList ob;
	ob.insertAtFront(new plane);
	bool updated = true;
	intersectableList displayed;
	



	sf::Sprite screen_s;
	screen_s.setTexture(screen_t);



	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{

			case sf::Event::Closed:
			{
				std::cout << "Closing" << std::endl;
				window.close();
				break;
			}

			case sf::Event::KeyPressed:
			{
				switch(event.key.code)
				{

				case sf::Keyboard::Escape:
				{
					std::cout << "Escaping" << std::endl;
					window.close();
					break;
				}	
				
				case sf::Keyboard::S:
				{
					double x = 0, y = 0, z = 0, r = 0;
					std::string input;
					std::cout <<"Sphere Creation" << std::endl << "x=";
					std::cin >> x;
					std::cout << "y=";
					std::cin >> y;
					std::cout << "z=";
					std::cin >> z;
					std::cout << "r=";
					std::cin >> r;
					ob.insertAtFront(new sphere(point(x,y,z),r));
					/*
					sf::Event text;
					while(window.pollEvent(text)!=sf::Event::TextEntered)
					{
					}
					input+=event.text.unicode;
					*/
					updated = true;
					break;
				}
				
				case sf::Keyboard::U:
				{
					std::cout << "Delete Object" << std::endl;
					ob.removeAtFront();
					updated = true;
					break;
				}

				}
				break;
			}
			
			}
			if(updated)
			{
				displayed.unlinkObjects();
				displayed.empty();
				std::cout << "Updated"<<std::endl;
				updated = false;

				
				for(int i = 0; i<rw*rh*4; i+=4)
				{
					int pixelNum = i/4;
					point onViewPlane = viewPlane.calculatePointFromPixel(pixelNum);
					vector v = fromTwoPoints(origin, onViewPlane);
					double closestIntersection = -1;
					bool intersected = false;	
					double lightStrength = 1;

					sf::Color intersectionColor;
					intersectable* intersector = ob.intersects(v,closestIntersection);
					if(intersector != NULL)
					{
						intersectionColor = intersector->getColor();
					}
					if(closestIntersection >0)
					{
						//closestIntersection is the t for vector v
						//pos point on shere
						intersected = true;
						point pos = pointFromVector(v,closestIntersection);
						lightStrength = intersector->lights(l1);
						double dirLight = intersector->lights(l2, pos);
						if(dirLight>=0)
						{
							lightStrength+=dirLight;
						}
						if(true)
						{
						intersectionColor.r = intersectionColor.r *lightStrength;
						intersectionColor.g = intersectionColor.g *lightStrength;
						intersectionColor.b = intersectionColor.b *lightStrength;
						}
					}
					/*
					double nextIntersection = floor.intersects(v);
					if(closestIntersection < 0||(nextIntersection > 0 && nextIntersection < closestIntersection) )
					{
						closestIntersection = nextIntersection;
						intersectionColor = floor.getColor();
					}
					if(closestIntersection > 0)
					{
						intersected = true;
					}
					*/
					if(intersected)
					{
						pixels[i + 0] = intersectionColor.r;
						pixels[i + 1] = intersectionColor.g;
						pixels[i + 2] = intersectionColor.b;
						pixels[i + 3] = 255;
					}
					else
					{
							pixels[i+0] = 135;
							pixels[i+1] = 206;
							pixels[i+2] = 235;
							pixels[i+3] = 255;
					}
				}
				screen_t.update(pixels);
			}
	
		}

		window.clear();
		
		window.draw(screen_s);

		window.display();
	}
	
	return 14;

}

