#include "BaseObject.h"

using namespace std;
using namespace sf;

#pragma region BaseObject

BaseObject::BaseObject(Vector2f position, string name)
{
	this->position = position;
	this->name = name;
}

string BaseObject::getName()
{
	return name;
}

#pragma endregion

#pragma region VisibleObject

VisibleObject::VisibleObject(Vector2f position, string name, string path) : 
	BaseObject(position, name)
{
	if (!texture.loadFromFile(path))
		texture.loadFromFile("Textures/none.png");

	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void VisibleObject::draw(RenderWindow& window)
{
	window.draw(sprite);
}

#pragma endregion
