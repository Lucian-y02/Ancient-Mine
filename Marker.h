#pragma once

#include "SFML/Graphics.hpp"
#include <string>

class Marker
{
private:

	sf::Rect<float> baseRect = sf::Rect<float>(sf::Vector2f(0, 0), sf::Vector2f(16, 16));
	sf::RectangleShape showRect;
	std::string moveSide;

public:

	Marker(sf::Vector2f position, std::string side, std::string moveSide);

	void draw(sf::RenderWindow& window);
	sf::Rect<float> getRect();
	std::string getMoveSide();
};
