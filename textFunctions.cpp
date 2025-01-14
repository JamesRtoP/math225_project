#include "textFunctions.hpp"


std::string recieveText(sf::RenderWindow& window)//will only exit upon a return or escape
{
	std::string input = "";
	sf::Event textEvent;
	bool broken = false;
	window.pollEvent(textEvent);//purge s
	while(!broken)
	{
		if(window.pollEvent(textEvent))
		{
			if(textEvent.type == sf::Event::TextEntered && textEvent.text.unicode != 8)
			{
				input+=textEvent.text.unicode;
			}
			if(textEvent.type == sf::Event::KeyPressed)
			{
				if(textEvent.key.code == sf::Keyboard::Escape)
				{
					input = "~";
					//std::cout <<
					broken = true;
				}
				else if(textEvent.key.code == sf::Keyboard::Return)
				{
					broken = true;
				}
				else if(textEvent.key.code == sf::Keyboard::BackSpace)
				{
					input.pop_back();
				}
			}
		}
	}
	return input;
}

void renderText(sf::RenderWindow& window,sf::Sprite& render, commandLine& cl)
{
    cl.setText();
	window.clear();
	window.draw(render);
	window.draw(cl.getBackground());
	window.draw(cl.getCommandText());
	window.display();
}

//could replace sprite and rectangle with a render list
std::string recieveText(sf::RenderWindow& window, sf::Sprite& render, commandLine& cl)//will only exit upon a return or escape
{

    renderText(window, render, cl);
	std::string input = "";
	sf::Event textEvent;
	bool broken = false;
	window.pollEvent(textEvent);//purge s
	while(!broken)
	{
		if(window.pollEvent(textEvent))
		{
            if(textEvent.type == sf::Event::Closed)
            {
                input = "~";
                //std::cout <<
                broken = true;
            }
			if(textEvent.type == sf::Event::TextEntered && textEvent.text.unicode != 8)
			{
				input+=textEvent.text.unicode;
				cl.setInput(input);
				renderText(window, render, cl);
				
			}
			if(textEvent.type == sf::Event::KeyPressed)
			{
				if(textEvent.key.code == sf::Keyboard::Escape)
				{
					input = "~";
					//std::cout <<
					broken = true;
				}
				else if(textEvent.key.code == sf::Keyboard::Return)
				{
					broken = true;
				}
				else if(textEvent.key.code == sf::Keyboard::BackSpace)
				{
                    if(input.size() > 0)
                    {
					    input.pop_back();
					    cl.setInput(input);
					    renderText(window, render, cl);
                    }

				}
			}
		}
	}
	return input;
}