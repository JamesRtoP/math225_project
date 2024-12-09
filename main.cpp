#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class point
{
private:
	double x;
	double y;
	double z;
public:
	point()
	{
		x=0;
		y=0;
		z=0;
	}

	point(double newX, double newY, double newZ)
	{
		x = newX;
		y = newY;
		z = newZ;
	}

	double getx(void) const
	{
		return x;
	}
	double gety(void) const
	{
		return y;
	}

	double getz(void) const
	{
		return z;
	}
	

};


std::ostream& operator<< (std::ostream& stream, const point & aPoint)
{
	stream << "(" << aPoint.getx() <<"," << aPoint.gety() << "," << aPoint.getz() << ")";
	return stream;
}

class vector
{
private:
	double xdir;
	double ydir;
	double zdir;
public:
	vector()
	{

		this->xdir = 0;
		this->ydir = 0;
		this->zdir = 0;
	}
	vector(double newXDir, double newYDir, double newZDir)
	{
		this->xdir = newXDir;
		this->ydir = newYDir;
		this->zdir = newZDir;
	}
	double getXDir(void) const
	{
		return this->xdir;
	}
	double getYDir(void) const
	{
		return this->ydir;
	}
	double getZDir(void) const
	{
		return this->zdir;
	}
	void setXDir(double newxdir)
	{
		this->xdir = newxdir;
	}
	void setYDir(double newydir)
	{
		this->ydir = newydir;
	}
	void setZDir(double newzdir)
	{
		this->zdir = newzdir;
	}
};

double dotProduct(vector one, vector two)
{
	return one.getXDir() * two.getXDir() +one.getYDir() * two.getYDir() + one.getZDir() * two.getZDir();	

}

class ray
{
private:
	vector dir;
	point origin;
	//x,y,z for start point
	double t;//length of vector ie t[x,z,y]
public:
	void setT(double newT)
	{
		this->t = newT;
	}
	void setDir(vector newDir)
	{
		this->dir = newDir;
	}
	void setOrigin(point newOrigin)
	{
		this->origin = newOrigin;
	}
	double getT(void) const
	{
		return this->t;
	}
	point getOrigin(void)
	{
		return this->origin;
	}
	vector getDir(void)
	{	
		return this->dir;
	}

};


std::ostream& operator<< (std::ostream& stream, const vector & printMe)
{
	stream << "[" << printMe.getXDir() <<"," << printMe.getYDir() << "," << printMe.getZDir() << "]";
	return stream;
}

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
	}
};

class ambientLight : public light
{
private:
protected:
public:
	ambientLight(double newPower, lightType newType):light(newPower, newType){}
	
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
	}
	//virtual double lights(
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
	//int width;
	//int height;
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
		this->color = sf::Color(0,0,0);
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
		this->color = sf::Color(0,0,0);
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
	return (-2 * b + sqrt(insideRoot))/(2*a);

}

double outsideTheRootNeg(double a, double b, double c, double insideRoot)
{
	return (-2 * b + sqrt(insideRoot))/(2*a);

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
		this->color = sf::Color(157,136,81);
		this->type = SPHERE;
	}

	sphere(point origin, double newRadius)
	{
		this->center = origin;
		this->radius = newRadius;
		this->color = sf::Color(157,136,81);
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
};


class intersectableNode
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
		if(object != NULL)
		{
			delete object;
		}
		if(pNext != NULL)
		{
			delete pNext;
		}
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
		//object = new intersectable(*(copyMe.object));
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
		return object;
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
	//screen_t.loadFromImage(screen);
	
	sf::Uint8* pixels = new sf::Uint8[rw*rh*4];
	
	/*
	for(int i = 0; i < rw; i++)//width
	{
		for(int j = 0; j < rh; j++)//height
		{//this goes top to bottom left to right i think
			for(int i = 0; i<4;i++)
			{
				pixels[i*j+i] = 255;
				pixels[i*j+i] = 255;
				pixels[i*j+i] = 255;
				pixels[i*j+i] = 255;
			}
		}
	}
	*/

	point origin(0,0,0);

	intersectable* objects;
	
	restrictedPlane viewPlane;//: = new restrictedPlane();
				  //
	sphere omega(point(0,5,0),2);
	plane floor;

	for(int i = 0; i<rw*rh*4; i+=4)
	{
		pixels[i+0] = 255;
		pixels[i+1] = 255;
		pixels[i+2] = 255;
		pixels[i+3] = 255;
		//vector dir = fromTwoPoints(,origin);
		int pixelNum = i/4;
		point onViewPlane = viewPlane.calculatePointFromPixel(pixelNum);
		vector v = fromTwoPoints(origin, onViewPlane);
		double closestIntersection = -1;
		bool intersected = false;	
		
		closestIntersection = omega.intersects(v);
		sf::Color intersectionColor = omega.getColor();

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

		if(intersected)
		{
			/*
				pixels[i+0] = 102;
				pixels[i+1] = 65;
				pixels[i+2] = 33;
				pixels[i+3] = 255;
				*/
			pixels[i + 0] = intersectionColor.r;
			pixels[i + 1] = intersectionColor.b;
			pixels[i + 2] = intersectionColor.g;
			pixels[i + 3] = 255;

		}
		else
		{
				pixels[i+0] = 0;
				pixels[i+1] = 0;
				pixels[i+2] = 214;
				pixels[i+3] = 255;
		}

		//last four lines are for debugging only REMOVE 
		if(pixelNum %(720*2) == 0)
		{
			screen_t.update(pixels);	
			sf::Sprite screen_s;
			screen_s.setTexture(screen_t);
			window.clear();
			
			window.draw(screen_s);

			window.display();
		}
	}
	

	screen_t.update(pixels);


	sf::Sprite screen_s;
	screen_s.setTexture(screen_t);



	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}

			}
	
		}

		window.clear();
		
		window.draw(screen_s);

		window.display();
	}
	
	return 14;

}

