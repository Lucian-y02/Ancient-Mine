#include "DamageObjects.h"

#include <iostream>

using namespace std;
using namespace sf;

#pragma region Spikes

Spikes::Spikes(string side) : BaseObject("spikes", "Textures/unNames.png", false) 
{
	this->side = side;
	damage = 2;

	if (side == "left" || side == "right")
		texture.loadFromFile("Textures/spikesVertical.png");
	else if (side == "top" || side == "down")
		texture.loadFromFile("Textures/spikesHorizontal.png");

	sprite.setTexture(texture);
	baseRect = sprite.getGlobalBounds();

	sprite.setPosition(Vector2f(-128, 0));
	position = sprite.getPosition();

	baseRect.left = position.x;
	baseRect.top = position.y;

	showRect.setPosition(position);
	showRect.setFillColor(Color(150, 50, 50));
	showRect.setSize(Vector2f(baseRect.width, baseRect.height));
};

void Spikes::setPosition(Vector2f newPosition)
{
	if (side == "down")
		position = Vector2f(newPosition.x * 64, newPosition.y * 64 + 64 - texture.getSize().y);
	else if (side == "top" || side == "left")
		position = Vector2f(newPosition.x * 64, newPosition.y * 64);
	else if (side == "right")
		position = Vector2f(newPosition.x * 64 + 64 - texture.getSize().x, newPosition.y * 64);

	sprite.setPosition(position);

	baseRect.left = position.x;
	baseRect.top = position.y;

	showRect.setPosition(position);
}

#pragma endregion
