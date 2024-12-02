#include <SFML/Graphics.hpp>


class point
{
private:
	int x;
	int y;
	int z;
public:
	point()
	{
		x=0;
		y=0;
		z=0;
	}

	point(int newX,int newY,int newZ)
	{
		x = newX;
		y = newY;
		z = newZ;
	}

	int getx(void)
	{
		return x;
	}
	int gety(void)
	{
		return y;
	}

	int getz(void)
	{
		return z;
	}
};

class vector
{
private:
	int xdir;
	int ydir;
	int zdir;
public:
	int getxdir(void)
	{
		return this->xdir;
	}
	int getydir(void)
	{
		return this->ydir;
	}
	int getzdir(void)
	{
		return this->zdir;
	}
	void setxdir(int newxdir)
	{
		this->xdir = newxdir;
	}
	void setydir(int newydir)
	{
		this->ydir = newydir;
	}
	void setzdir(int newzdir)
	{
		this->zdir = newzdir;
	}
};



class sphere
{
private:
	point center;
	int radius;
};

class plane//restricted plane //using equation a(x-x1)+b(y-y1)+c(z-z1) = 0
{
	//int width;
	//int height;
private:
	//directional offsets
	//also where the plane is "centered" for view port
	int x;
	int y;
	int z;

	int a;
	int b;
	int c;

public:
	plane(int newX, int newY, int newZ)
	{
		this->x = newX;
		this->y = newY;
		this->z = newZ;
	}
	
};

class restrictedPlane:plane
{
	int width;
	int height;
};


vector fromTwoPoints(point from, point to)
{
	vector returnVector;
	returnVector.setxdir(to.getx()-from.getx());
	returnVector.setydir(to.gety()-from.gety());
	returnVector.setzdir(to.getz()-from.getz());
	return returnVector;
}

int main(void)
{

	sf::RenderWindow window(sf::VideoMode(500,500), "View Port");

	sf::Image screen;
	screen.loadFromFile("assets/orangy_1000x1000.png");
	int render_width = 500;
	int render_height = 500;
	int& rh = render_height;
	int& rw = render_width;

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

	for(int i = 0; i<rw*rh*4; i++)
	{
		//vector dir = fromTwoPoints(,origin);
		pixels[i] = 255;
                pixels[i+1] = 255;
                pixels[i+2] = 255;
                pixels[i+3] = 255;
	}
	

	screen_t.update(pixels);


	sf::Sprite screen_s;
	screen_s.setTexture(screen_t);


	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
	
		}

		window.clear();
		
		window.draw(screen_s);

		window.display();
	}
	
	return 14;

}
