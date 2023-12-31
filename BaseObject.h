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
	sf::RectangleShape showRect;
	sf::Rect<float> baseRect;
	bool rectanglesVisible = false;
	bool destroyed = false;
	int damage = 0;

public:

	BaseObject(sf::Vector2f position, std::string name = "unNamed",
		std::string path = "Textures/unNamed.png", bool loadTexture = true);
	BaseObject(std::string name = "unNamed", std::string path = "Textures/unNamed.png",
		bool loadTexture = true);

	virtual void update(double delta);
	virtual void draw(sf::RenderWindow& window);
	virtual void startProcess();
	std::string getName();
	virtual void setPosition(sf::Vector2f newPosition);
	virtual double getValue();
	void showRectangles();
	sf::Rect<float>& getRect();
	bool isDestroyed();
};

