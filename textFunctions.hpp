#ifndef textFunctions_HPP
#define textFunctions_HPP

#include "source.hpp"
#include "commandLine.hpp"

//text functions
std::string recieveText(sf::RenderWindow& window);//will only exit upon a return or escape
std::string recieveText(sf::RenderWindow& window,sf::Sprite& render, commandLine& cl);//will only exit upon a return or escape

//double makeDouble(const std::string& makeMeDouble);

#endif