#include "source.hpp"
#include "basic_geometry.hpp"
#include "light.hpp"
#include "intersectable.hpp"
#include "commandLine.hpp"
#include "textFunctions.hpp"


//I could make it a hash table, that would be pretty fire
//hash by node type
int main(void)
{
	/*
	sf::RectangleShape commandLine(sf::Vector2f(720,25));
	commandLine.setPosition(sf::Vector2f(0,720-25));
	commandLine.setFillColor(sf::Color::White);
	sf::Font commandFont;
	
	sf::Text command("Yes Sire",commandFont);
	command.setFillColor(sf::Color::Black);
	command.setPosition(0,720-command.getGlobalBounds().height-command.getGlobalBounds().top);
	*/
	//command.


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
	
	commandLine cl;
	//commandLine wassup;



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
					bool exitSphereCreation = false;
					bool createSphere = false;
					bool validInput = false;
					int parameterIndex = 0;
					double parameters[4];//x,y,z,r
					std::string input;
					std::string prompt = "x = ";
					while(!exitSphereCreation)
					{
						while(!validInput)
						{
							//double x = 0, y = 0, z = 0, r = 0;
							std::cout << prompt << std::endl;
							cl.setPrompt(prompt);
							input = recieveText(window, screen_s, cl);
							std::string token;
							for(int i = 0; input[i] != '\0'; i++)
							{
								if(input == "~")
								{
									validInput = true;
									exitSphereCreation = true;
								}
								else if(input[i] != ' ')
								{
									token.push_back(input.at(i));
								}
								else
								{
									if(isDouble(token) && parameterIndex < 4)
									{
										parameters[parameterIndex] = stod(token);
										parameterIndex++;
										validInput = true;
									}
									else
									{
										validInput = false;
										break;
									}
									token = "";
								}
							}
							if(isDouble(token) && parameterIndex < 4)
							{
								parameters[parameterIndex] = stod(token);
								parameterIndex++;
								validInput = true;
							}
							else
							{
								validInput = false;
								break;
							}
							
						}
						std::string frontReplacement = "";
						prompt = "";
						if(!exitSphereCreation)
						{
							switch(parameterIndex)
							{
								case 4:
								{
									exitSphereCreation = true;
									prompt = std::to_string(parameters[3]);
									createSphere = true;
								}
								case 3:
								{
									prompt.insert(0,", r = ");
									prompt.insert(0,std::to_string(parameters[2]));
								}
								case 2:
								{
									prompt.insert(0,", z = ");
									prompt.insert(0,std::to_string(parameters[1]));
								}
								case 1:
								{
									prompt.insert(0,", y = ");
									prompt.insert(0,std::to_string(parameters[0]));
									prompt.insert(0,"x = ");
									break;
								}
								case 0:
								{
									prompt = "x = ";
								}
							}
						}
						//cl.setPrompt(prompt);
						validInput = false;
					}
					//updated = true;
					std::cout << prompt << std::endl;
					if(createSphere == true)
					{
						ob.insertAtFront(new sphere(point(parameters[0],parameters[1],parameters[2]),parameters[3]));
						updated = true;
					}
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
		//window.draw(wassup.getBackground());

		//window.draw(wassup.getCommandText());
		//window.draw(commandLine);
		//window.draw(command);

		window.display();
	}
	
	return 14;

}

