#pragma once

#include "SFML/Graphics.hpp"
#include <string>

class BaseObject
{
protected:

	std::string name;
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Rect<float> baseRect;

public:

	BaseObject(sf::Vector2f position, std::string name = "unNamed", 
		std::string path = "Textures/unNamed.png");
	BaseObject(std::string name = "unNamed", std::string path = "Textures/unNamed.png");

	virtual void update(double delta);
	virtual void draw(sf::RenderWindow& window);
	std::string getName();
	virtual void setPosition(sf::Vector2f newPosition);
};

