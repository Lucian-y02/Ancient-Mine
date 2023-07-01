#include "BaseObject.h"

using namespace std;
using namespace sf;

BaseObject::BaseObject(Vector2f position, string name, string path, bool loadTexture)
{
	this->name = name;

	if (loadTexture)
	{
		texture.loadFromFile(path);

		sprite.setTexture(texture);
		baseRect = sprite.getGlobalBounds();

		sprite.setPosition(Vector2f(position.x * 64.0 + (64.0 - texture.getSize().x) / 2,
			position.y * 64.0));
		position = sprite.getPosition();

		baseRect.left = position.x;
		baseRect.top = position.y;

		showRect.setPosition(position);
		showRect.setSize(Vector2f(baseRect.width, baseRect.height));
	}
}

BaseObject::BaseObject(string name, string path, bool loadTexture)
{
	this->name = name;

	if (loadTexture)
	{
		texture.loadFromFile(path);

		sprite.setTexture(texture);
		baseRect = sprite.getGlobalBounds();

		sprite.setPosition(Vector2f(-128, 0));
		position = sprite.getPosition();

		baseRect.left = position.x;
		baseRect.top = position.y;

		showRect.setPosition(position);
		showRect.setSize(Vector2f(baseRect.width, baseRect.height));
	}
}

void BaseObject::draw(RenderWindow& window)
{
	window.draw(sprite);

	if (rectanglesVisible)
	{
		window.draw(showRect);
	}
}

void BaseObject::update(double delta) {}

string BaseObject::getName()
{
	return name;
}

void BaseObject::setPosition(Vector2f newPosition)
{
	position = Vector2f(newPosition.x * 64.0, newPosition.y * 64.0);
	sprite.setPosition(position);

	baseRect.left = position.x;
	baseRect.top = position.y;

	showRect.setPosition(position);
}

int BaseObject::getDamage()
{
	return damage;
}

void BaseObject::showRectangles()
{
	rectanglesVisible = !rectanglesVisible;
}

Rect<float>& BaseObject::getRect()
{
	return baseRect;
}
