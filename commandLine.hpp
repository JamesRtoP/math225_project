#include "source.hpp"

#ifndef commandLine_HPP
#define commandLine_HPP

class commandLine
{
private:
sf::RectangleShape background;
sf::Font commandFont;
sf::Text commandText;
std::string prompt;
std::string input;
public:

commandLine(void);
sf::RectangleShape getBackground(void);
sf::Text getCommandText(void);
void setInput(std::string command);
void setPrompt(std::string newPrompt);
void setText(void);
};

#endif