#pragma once

#include "BaseObject.h"
#include "SFML/Graphics.hpp"

class Wall: public BaseObject
{
public:

	Wall();
	Wall(sf::Vector2f position);
};

