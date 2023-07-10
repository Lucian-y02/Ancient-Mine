#include "Marker.h"

using namespace sf;

Marker::Marker(Vector2f position, std::string side, std::string moveSide)
{
	this->moveSide = moveSide;

	if (side == "right")
	{
		baseRect.left = (position.x + 1) * 64.0;
		baseRect.top = position.y * 64.0 + (64 - baseRect.height) / 2;
	}
	else if (side == "left")
	{
		baseRect.left = position.x * 64.0 - baseRect.width;
		baseRect.top = position.y * 64.0 + (64 - baseRect.height) / 2;
	}
	else if (side == "down")
	{
		baseRect.left = position.x * 64.0 + (64 - baseRect.width) / 2;
		baseRect.top = (position.y + 1) * 64.0;
	}
	else if (side == "top")
	{
		baseRect.left = position.x * 64.0 + (64 - baseRect.width) / 2;
		baseRect.top = position.y * 64.0 - baseRect.height;
	}

	showRect.setSize(Vector2f(baseRect.width, baseRect.height));
	showRect.setPosition(Vector2f(baseRect.left, baseRect.top));
	showRect.setFillColor(Color(150, 75, 0));
}

void Marker::draw(RenderWindow& window)
{
	window.draw(showRect);
}

Rect<float> Marker::getRect()
{
	return baseRect;
}

std::string Marker::getMoveSide()
{
	return moveSide;
}
