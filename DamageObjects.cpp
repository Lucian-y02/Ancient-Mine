#include "DamageObjects.h"

using namespace std;
using namespace sf;

#pragma region Spikes

Spikes::Spikes(string side) : BaseObject("spikes", "Textures/spikes.png") 
{
	this->side = side;
};

void Spikes::setPosition(Vector2f newPosition)
{
	position = Vector2f(newPosition.x * 64, newPosition.y * 64 + 64 - texture.getSize().y);
	sprite.setPosition(position);
}

int Spikes::getDamage()
{
	return damage;
}

#pragma endregion
