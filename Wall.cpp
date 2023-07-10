#include "Wall.h"

#include <iostream>

using namespace std;
using namespace sf;

#pragma region Wall

Wall::Wall() : BaseObject("wall", "Textures/orangeBox.png") 
{
	showRect.setFillColor(Color(100, 100, 100));
};

Wall::Wall(Vector2f position) : BaseObject(position, "wall", "Textures/orangeBox.png") 
{
	showRect.setFillColor(Color(100, 100, 100));
}

#pragma endregion

Platform::Platform() : BaseObject("platform", "Textures/platform.png")
{
	showRect.setFillColor(Color(210, 210, 210));
}

#pragma region SelfDestructionBlock

SelfDestructiveBlock::SelfDestructiveBlock() :
	BaseObject("selfDestructiveBlock", "Textures/selfDestructiveBlock.png")
{
	this->destroyCoolDown = destroyCoolDown;

	showRect.setFillColor(Color(50, 50, 200));
	indicatorColor = Color(200, 50, 50, 0);

	indicator.setSize(Vector2f(baseRect.width, baseRect.height));
	indicator.setFillColor(indicatorColor);
}

void SelfDestructiveBlock::update(double delta)
{
	if (start)
	{
		destroyTimer += delta;
		indicatorColor = Color(200, 50, 50, (255 / (destroyCoolDown + 1.5)) * destroyTimer);
		indicator.setFillColor(indicatorColor);
	}
		
	if (destroyTimer >= destroyCoolDown)
		destroyed = true;
}

void SelfDestructiveBlock::draw(RenderWindow& window)
{
	if (rectanglesVisible)
		window.draw(showRect);
	else
		window.draw(sprite);

	if (start)
		window.draw(indicator);
}

void SelfDestructiveBlock::startProcess()
{
	start = true;
}

void SelfDestructiveBlock::setPosition(Vector2f newPosition)
{
	position = Vector2f(newPosition.x * 64.0, newPosition.y * 64.0);
	sprite.setPosition(position);

	baseRect.left = position.x;
	baseRect.top = position.y;

	showRect.setPosition(position);
	indicator.setPosition(position);
}

#pragma endregion

#pragma region JumpBoost

JumpBoost::JumpBoost() : BaseObject("jumpBoost", "Textures/jumpBoost.png")
{
	showRect.setFillColor(Color(50, 150, 50));
}

double JumpBoost::getValue()
{
	return boostValue;
}

#pragma endregion

#pragma region MoveObject

MoveObject::MoveObject(string moveSide, string name, string path) :
	BaseObject(name, path)
{
	this->field = field;
	this->moveSide = moveSide;

	additionalRect.width = 58;
	additionalRect.height = 58;

	showRect.setFillColor(Color(100, 100, 100));
	showAdditionalRect.setFillColor(Color(50, 50, 50));
	showAdditionalRect.setSize(Vector2f(additionalRect.width, additionalRect.height));
}

void MoveObject::draw(RenderWindow& window)
{
	if (rectanglesVisible)
	{
		window.draw(showRect);
		window.draw(showAdditionalRect);

		for (Marker marker : markers)
		{
			marker.draw(window);
		}
	}
	else
		window.draw(sprite);
}

void MoveObject::update(double delta)
{
	if (this->checkMarkers())
	{
		this->setPosition(Vector2f(position.x / 64, position.y / 64));
	}
	
	velocity = moveSideMap[moveSide];

	velocity.x *= speed * delta;
	velocity.y *= speed * delta;

	position += velocity;

	sprite.setPosition(position);

	baseRect.left = position.x;
	baseRect.top = position.y;

	additionalRect.left = position.x + (64.0 - additionalRect.width) / 2;
	additionalRect.top = position.y + (64.0 - additionalRect.height) / 2;

	showRect.setPosition(position);
	showAdditionalRect.setPosition(Vector2f(additionalRect.left, additionalRect.top));
}

void MoveObject::setPosition(Vector2f newPosition)
{
	sprite.setPosition(Vector2f(newPosition.x * 64.0, newPosition.y * 64.0));
	position = sprite.getPosition();

	baseRect.left = position.x;
	baseRect.top = position.y;

	additionalRect.left = position.x + (64.0 - additionalRect.width) / 2;
	additionalRect.top = position.y + (64.0 - additionalRect.height) / 2;

	showRect.setPosition(position);
	showAdditionalRect.setPosition(Vector2f(additionalRect.left, additionalRect.top));
}

void MoveObject::addMarker(Vector2f position, string side, string moveSide)
{
	markers.push_back(Marker(position, side, moveSide));
}

bool MoveObject::checkMarkers()
{
	isFinded = false;

	for (size_t i = 0; i < markers.size() && !isFinded; i++)
	{
		if (baseRect.intersects(markers[i].getRect()))
		{
			moveSide = markers[i].getMoveSide();
			isFinded = true;
		}
	}

	return isFinded;
}

double MoveObject::getValue()
{
	if (moveSide == "left")
		return -speed;
	else if (moveSide == "right")
		return speed;
	else
		return 0;
}

map<string, Vector2f> MoveObject::moveSideMap = {
	{"top", Vector2f(0, -1)},
	{"down", Vector2f(0, 1)},
	{"left", Vector2f(-1, 0)},
	{"right", Vector2f(1, 0)}
};

#pragma endregion

MoveWall::MoveWall(string moveSide) : MoveObject(moveSide, "moveWall", "Textures/orangeBox.png") 
{
	speed = 100;
}
