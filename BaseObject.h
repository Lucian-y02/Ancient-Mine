#pragma once

#include "SFML/Graphics.hpp"
#include <string>

class BaseObject
{
protected:

	sf::Vector2f position;
	std::string name;

public:

	BaseObject(sf::Vector2f position, std::string name = "none");

	virtual void update(double delta) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	std::string getName();
};

class VisibleObject : public BaseObject
{
protected:

	sf::Sprite sprite;
	sf::Texture texture;

public:

	VisibleObject(sf::Vector2f position, std::string name = "none", 
		std::string path = "Textures/none.png");

	void draw(sf::RenderWindow& window) override;
};
