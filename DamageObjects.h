#pragma once

#include "BaseObject.h"
#include "SFML/Graphics.hpp"

class Spikes : public BaseObject
{
protected:

	int damage = 2;
	std::string side;

public:

	Spikes(std::string side);

	void setPosition(sf::Vector2f newPosition) override;
	int getDamage();
};
