#include "Player.h"
#include <iostream>

using namespace std;
using namespace sf;

Player::Player(vector<vector<BaseObject*>>& field, string controlType) :
	BaseObject("player", "Textures/player.png") 
{
	this->controlType = controlType;
	this->field = field;

	// Отображение для основного прямоугольника
	showRect.setSize(Vector2f(baseRect.width, baseRect.height));
	showRect.setFillColor(Color(0, 200, 0, 150));

	// Инициализация дополнительного прямоугольника
	additionalRect.width = texture.getSize().x - (2 * shiftWidth);
	additionalRect.height = texture.getSize().y - shiftHeight;

	// Отображение для дополнительного прямоугольника
	showAdditionalRect.setSize(Vector2f(additionalRect.width, additionalRect.height));
	showAdditionalRect.setFillColor(Color(0, 0, 200, 150));
}

Player::Player(Vector2f position, vector<vector<BaseObject*>>& field, string controlType) :
	BaseObject(position, "player", "Textures/player.png") 
{
	this->controlType = controlType;
	this->field = field;

	// Отображение для основного прямоугольника
	showRect.setSize(Vector2f(baseRect.width, baseRect.height));
	showRect.setPosition(Vector2f(baseRect.left, baseRect.top));
	showRect.setFillColor(Color(0, 200, 0, 150));

	// Инициализация дополнительного прямоугольника
	additionalRect.width = texture.getSize().x - (2 * shiftWidth);
	additionalRect.height = texture.getSize().y - shiftHeight;
	additionalRect.left = position.x + shiftWidth;
	additionalRect.top = position.y + shiftHeight;

	// Отображение для дополнительного прямоугольника
	showAdditionalRect.setSize(Vector2f(additionalRect.width, additionalRect.height));
	showAdditionalRect.setPosition(Vector2f(additionalRect.left, additionalRect.top));
	showAdditionalRect.setFillColor(Color(0, 0, 200, 150));
}

void Player::update(double delta)
{
	velocity = Vector2f(0, 0);
	
	// Проверка на нажатия кнопок
	if (controlType == "keyboard")
		this->checkPressedKeyboard();
	else if (controlType == "joystickX")
		this->checkPressedJoystickX();
	else if (controlType == "joystickD")
		this->checkPressedJoystickD();

	// Изменение инерции во время прыжка
	if (!onGround)
		velocity.x *= 1.2;

	velocity.x *= speed * delta;
	position += velocity;
	this->checkCollision('x'); // Проверка столкновений по оси OX
	velocity = Vector2f(0, 0);

	// Обработка прыжка
	if (!onGround)
	{
		velocity += jumpForceNow;

		// Изменение гравитации после отпускания клавиши
		if (jumpForceNow.y < 0)
		{
			jumpForceNow.y *= n;
		}

		// Влияние гравитации
		jumpForceNow += gravity;
	}

	if (velocity.y == 0)
	{
		onGround = false;
		jumpForceNow = gravity;
	}

	velocity.y *= delta;
	position += velocity;
	this->checkCollision('y'); // Проверка столкновений по оси OY

	sprite.setPosition(position);

	// Перемещение прямоугольников
	baseRect.left = position.x;
	baseRect.top = position.y;
	additionalRect.left = position.x + shiftWidth;
	additionalRect.top = position.y + shiftHeight;
	showRect.setPosition(position);
	showAdditionalRect.setPosition(Vector2f(additionalRect.left, additionalRect.top));
}

void Player::draw(RenderWindow& window)
{
	window.draw(sprite);

	if (rectanglesVisible)
	{
		window.draw(showRect);
		window.draw(showAdditionalRect);
	}
}

void Player::setPosition(Vector2f newPosition)
{
	position = Vector2f(newPosition.x * 64 + (64 - texture.getSize().x) / 2, newPosition.y * 64);
	sprite.setPosition(position);

	baseRect.left = position.x;
	baseRect.top = position.y;

	additionalRect.left = position.x + shiftWidth;
	additionalRect.top = position.y + shiftHeight;

	showRect.setPosition(position);
	showAdditionalRect.setPosition(Vector2f(additionalRect.left, additionalRect.top));
}

void Player::checkCollision(char axis)
{
	string objectName;

	for (int x = (int)(position.x) / 64; x <= ((int)(position.x) + texture.getSize().x) / 64; x++)
	{
		for (int y = (int)(position.y) / 64; y <= ((int)(position.y) + texture.getSize().y) / 64; y++)
		{
			if (field[x][y] != NULL)
			{
				objectName = field[x][y]->getName();

				if (objectName == "wall")
				{
					if (axis == 'x')
					{
						if (velocity.x > 0)
						{
							position.x = x * 64 - texture.getSize().x - 0.1;
						}
						else if (velocity.x < 0)
						{
							position.x = (x + 1) * 64 + 0.1;
						}
					}
					else if (axis == 'y')
					{
						if (velocity.y > 0)
						{
							position.y = y * 64 - texture.getSize().y - 0.1;
							onGround = true;
							n = 1;
							jumpForceNow = jumpForce;
						}
						else if (velocity.y < 0)
						{
							jumpForceNow.y = 0;
							position.y = (y + 1) * 64 + 0.1;
						}
					}
				}
			}
		}
	}
}

void Player::checkPressedKeyboard()
{
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		velocity -= Vector2f(1, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		velocity += Vector2f(1, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::W) && onGround && jumpReady)
	{
		onGround = false;
		jumpReady = false;
	}
	if (!Keyboard::isKeyPressed(Keyboard::W) && !onGround)
	{
		n = 0.55;
	}
	if (!Keyboard::isKeyPressed(Keyboard::W) && onGround)
	{
		jumpReady = true;
	}
}

void Player::checkPressedJoystickX()
{
	if (Joystick::getAxisPosition(0, Joystick::PovX) == -100 ||
		Joystick::getAxisPosition(0, Joystick::X) < -50)
	{
		velocity -= Vector2f(1, 0);
	}
	if (Joystick::getAxisPosition(0, Joystick::PovX) == 100 ||
		Joystick::getAxisPosition(0, Joystick::X) > 10)
	{
		velocity += Vector2f(1, 0);
	}
	if (Joystick::isButtonPressed(0, 0) && onGround && jumpReady)
	{
		onGround = false;
		jumpReady = false;
	} 
	if (!Joystick::isButtonPressed(0, 0) && !onGround)
	{
		n = 0.55;
	}
	if (!Joystick::isButtonPressed(0, 0) && onGround)
	{
		jumpReady = true;
	}
}

void Player::checkPressedJoystickD()
{
	if (Joystick::getAxisPosition(0, Joystick::PovX) == -100 ||
		Joystick::getAxisPosition(0, Joystick::X) == -100)
	{
		velocity -= Vector2f(1, 0);
	}
	if (Joystick::getAxisPosition(0, Joystick::PovX) == 100 ||
		Joystick::getAxisPosition(0, Joystick::X) == 100)
	{
		velocity += Vector2f(1, 0);
	}
	if (Joystick::isButtonPressed(0, 2) && onGround && jumpReady)
	{
		onGround = false;
		jumpReady = true;
	}
	if (!Joystick::isButtonPressed(0, 2) && !onGround)
	{
		n = 0.55;
	}
	if (!Joystick::isButtonPressed(0, 2) && onGround)
	{
		jumpReady = true;
	}
}

bool Player::isAlive()
{
	return (health > 0);
}

void Player::setField(std::vector<std::vector<BaseObject*>>& field)
{
	this->field = field;
}

void Player::setEnableImmortality(bool value)
{
	immortal = value;
}

void Player::showRectangles()
{
	rectanglesVisible = !rectanglesVisible;
}
