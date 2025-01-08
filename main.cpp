#include "source.hpp"
#include "basic_geometry.hpp"
#include "light.hpp"
#include "intersectable.hpp"



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


	//window.setKeyRepeatEnabled(false);	
	window.setKeyRepeatEnabled(false);
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
					
					/*
					std::cout <<"Sphere Creation" << std::endl << "x=";
					std::cin >> x;
					std::cout << "y=";
					std::cin >> y;
					std::cout << "z=";
					std::cin >> z;
					std::cout << "r=";
					std::cin >> r;
					ob.insertAtFront(new sphere(point(x,y,z),r));
					*/


					double x = 0, y = 0, z = 0, r = 0;
					std::string gar = recieveText(window);
					std::cout << gar <<std::endl;
					if(isDouble(gar))
					{
						std::cout << "That is a double" << std::endl;
					}
					else
					{
						std::cout << "That is not a double" << std::endl;
					}


					//updated = true;
					break;
				}
				
				case sf::Keyboard::U:
				{
					std::cout << "Delete Object" << std::endl;
					ob.removeAtFront();
					updated = true;
					break;
				}

				case sf::Keyboard::R:
				{
					std::cout << "R" << std::endl;
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

