#pragma once

#include "BaseObject.h"
#include "Marker.h"
#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <map>

class Wall : public BaseObject
{
public:

	Wall();
	Wall(sf::Vector2f position);
};

class Platform : public BaseObject
{
public:

	Platform();
};

class SelfDestructiveBlock : public BaseObject
{
private:

	sf::RectangleShape indicator;
	sf::Color indicatorColor;
	double destroyTimer = 0.0;
	double destroyCoolDown = 0.75;
	bool start = false;

public:

	SelfDestructiveBlock();

	void update(double delta) override;
	void draw(sf::RenderWindow& window) override;
	void setPosition(sf::Vector2f newPosition) override;
	void startProcess() override;
};

class JumpBoost : public BaseObject
{
private:

	double boostValue = 300;

public:

	JumpBoost();
	
	double getValue() override;
};

class MoveObject : public BaseObject
{
protected:
	// Вспомогательные переменные
	bool isFinded = false;

	std::string moveSide;
	std::vector<Marker> markers;
	double speed = 150;
	sf::Vector2f velocity;

public:

	static std::map<std::string, sf::Vector2f> moveSideMap;

	MoveObject(std::string moveSide, std::string name = "unNamed",
		std::string path = "Textures/unNamed");
	
	void draw(sf::RenderWindow& window) override;
	void update(double delta) override;
	void setPosition(sf::Vector2f newPosition) override;
	void addMarker(sf::Vector2f position, std::string side, std::string moveSide);
	double getValue() override;
	bool checkMarkers();

};

class MoveWall : public MoveObject
{
public:

	MoveWall(std::string moveSide);
};
