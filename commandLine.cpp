#include "commandLine.hpp"

commandLine::commandLine(void)
{
	this->background.setFillColor(sf::Color::White);
    this->background.setSize(sf::Vector2f(720,30));
    this->background.setPosition(sf::Vector2f(0,720-this->background.getGlobalBounds().height));
	

    

	//this->commandText.


    if(!this->commandFont.loadFromFile("./assets/Philosopher-Regular.ttf"))
	{
		std::cout << "Font Failure" << std::endl;
	}
	else
	{
		commandText.setFont(this->commandFont);
	}

	this->commandText.setFillColor(sf::Color::Black);
	this->commandText.setString("Error-ygp");
	this->commandText.setPosition(0,720-commandText.getGlobalBounds().height-commandText.getGlobalBounds().top);
	this->commandText.setString("");

	this->input = "";//dynamic user input
	this->prompt = "";//semi static prompt
}


sf::RectangleShape commandLine::getBackground(void)
{
	return this->background;
}

sf::Text commandLine::getCommandText(void)
{
	return this->commandText;
}

void commandLine::setInput(std::string command)
{
	this->input = command;
}

void commandLine::setText(void)
{

	this->commandText.setString(this->prompt + this->input);
}

void commandLine::setPrompt(std::string newPrompt)
{
	this->prompt = newPrompt;
}
