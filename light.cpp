#include "light.hpp"

double light::getPower(void)
{
    return this->power;
}	

void light::setPower(double newPower)
{
    this->power = newPower;
}

lightType light::getType(void)
{
    return this->type;
}

light::light(double newPower, lightType newType)
{
    this->power = newPower;
    this->type = newType;
    this->color = sf::Color::White;
}


ambientLight::ambientLight(double newPower):light(newPower, AMBIENT)
{
}


directionalLight::directionalLight(double newPower,vector newDir):light(newPower, DIRECTIONAL)
{
    this->dir = newDir;
}

vector directionalLight::getDir(void)
{
    return this->dir;
}

void directionalLight::setDir(vector newDir)
{
    this->dir = newDir;
}
