#ifndef SOURCE_HPP
#define SOURCE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

//math functions
//these functions are both for the quadratic formula
double outsideTheRootPos(double a, double b, double c, double insideRoot);
double outsideTheRootNeg(double a, double b, double c, double insideRoot);
double insideTheRoot(double a, double b, double c);
double quadraticFormulaUnsafePositiveRoot(double a, double b, double c);//no check for negative sqrt
double quadraticFormulaUnsafeNegativeRoot(double a, double b, double c);//no check for negative sqrt


//text functions
std::string recieveText(sf::Window& window);//will only exit upon a return or escape
bool isDouble(const std::string& checkMe);

//double makeDouble(const std::string& makeMeDouble);

#endif