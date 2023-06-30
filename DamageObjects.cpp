#include "DamageObjects.h"

using namespace std;
using namespace sf;

#pragma region Spikes

Spikes::Spikes(string side) : BaseObject("spikes", "Textures/spikes.png") 
{
	this->side = side;
	damage = 2;

	showRect.setFillColor(Color(150, 50, 50));
};

void Spikes::setPosition(Vector2f newPosition)
{
	position = Vector2f(newPosition.x * 64, newPosition.y * 64 + 64 - texture.getSize().y);
	sprite.setPosition(position);

	baseRect.left = position.x;
	baseRect.top = position.y;

	showRect.setPosition(position);
}

#pragma endregion
