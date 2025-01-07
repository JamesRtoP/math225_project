#include "source.hpp"
#include "basic_geometry.hpp"

enum lightType
{
	AMBIENT, DIRECTIONAL, POINT
};

class light
{
private:
protected:
	double power;
	lightType type;
	sf::Color color;
public:
	light(double newPower, lightType newType);
	double getPower(void);
	void setPower(double newPower);
	lightType getType(void);
};

class ambientLight : public light
{
private:
protected:
public:
	ambientLight(double newPower);
};

class directionalLight : public light
{
private:
	vector dir;
protected:
public:
	directionalLight(double newPower,vector newDir);
	vector getDir(void);
	void setDir(vector newDir);
};