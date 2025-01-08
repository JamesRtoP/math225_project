#include "source.hpp"

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

std::string recieveText(sf::Window& window)//will only exit upon a return or escape
{
	std::string input = "";
	sf::Event textEvent;
	bool broken = false;
	window.pollEvent(textEvent);//purge s
	while(!broken)
	{
		if(window.pollEvent(textEvent))
		{
			if(textEvent.type == sf::Event::TextEntered)
			{
				input+=textEvent.text.unicode;
			}
			if(textEvent.type == sf::Event::KeyPressed)
			{
				if(textEvent.key.code == sf::Keyboard::Escape)
				{
					input = "";
					//std::cout <<
					broken = true;
				}
				else if(textEvent.key.code == sf::Keyboard::Return)
				{
					broken = true;
				}
				else if(textEvent.key.code == sf::Keyboard::Return)
				{
					input.pop_back();
				}
			}
		}
	}
	return input;
}