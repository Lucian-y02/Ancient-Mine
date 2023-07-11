#include "Player.h"
#include <iostream>

using namespace std;
using namespace sf;

#pragma region HealthBar

HealthBar::HealthBar()
{
	health = 0;

	healthPoint.setSize(Vector2f(15, 25));
	healthPoint.setFillColor(Color(165, 48, 48, 200));
}

void HealthBar::update(int health)
{
	this->health = health;
}

void HealthBar::draw(RenderWindow& window)
{
	for (int i = 0; i < health; i++)
	{
		healthPoint.setPosition(Vector2f(30 + (17 * i), 30));
		window.draw(healthPoint);
	}
}

#pragma endregion

Player::Player(vector<vector<BaseObject*>>& field, 
	vector<MoveObject*>& moveObjects,
	string controlType) :
	BaseObject("player", "Textures/player.png") 
{
	this->controlType = controlType;
	this->field = field;
	this->moveObjects = moveObjects;

	healthBar.update(health);

	// Отображение для основного прямоугольника
	showRect.setSize(Vector2f(baseRect.width, baseRect.height));
	showRect.setFillColor(Color(50, 150, 50));

	// Инициализация дополнительного прямоугольника
	additionalRect.width = texture.getSize().x - (2 * shiftWidth);
	additionalRect.height = texture.getSize().y - (2 * shiftHeight);

	// Отображение для дополнительного прямоугольника
	showAdditionalRect.setSize(Vector2f(additionalRect.width, additionalRect.height));
	showAdditionalRect.setFillColor(Color(50, 50, 150));

	// Отображение давлений
	showPressure.setSize(Vector2f(20, 20));
	showPressure.setFillColor(Color(50, 200, 50));
}

Player::Player(Vector2f position, vector<vector<BaseObject*>>& field, string controlType) :
	BaseObject(position, "player", "Textures/player.png") 
{
	this->controlType = controlType;
	this->field = field;

	healthBar.update(health);

	// Отображение для основного прямоугольника
	showRect.setSize(Vector2f(baseRect.width, baseRect.height));
	showRect.setPosition(Vector2f(baseRect.left, baseRect.top));
	showRect.setFillColor(Color(50, 150, 50));

	// Инициализация дополнительного прямоугольника
	additionalRect.width = texture.getSize().x - (2 * shiftWidth);
	additionalRect.height = texture.getSize().y - (2 * shiftHeight);
	additionalRect.left = position.x + shiftWidth;
	additionalRect.top = position.y + shiftHeight;

	// Отображение для дополнительного прямоугольника
	showAdditionalRect.setSize(Vector2f(additionalRect.width, additionalRect.height));
	showAdditionalRect.setPosition(Vector2f(additionalRect.left, additionalRect.top));
	showAdditionalRect.setFillColor(Color(50, 50, 150));

	// Отображение давлений
	showPressure.setSize(Vector2f(20, 20));
	showPressure.setFillColor(Color(50, 200, 50));
}

void Player::update(double delta)
{
	// Обновление таймеров
	// Эффект бессмертия при получении урона
	if (immortal)
	{
		immortalTimer += delta;

		// Мигание при бессмертии
		visibleCounter++;
		if (visibleCounter % 3 == 0)
			visible = !visible;

		if (immortalTimer >= immortalCoolDown)
		{
			immortal = false;
			visible = true;
		}		
	}

	// Обнуление переменных
	velocity = Vector2f(0, 0);
	sidePressure = { 0, 0, 0, 0 };
	
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
	this->checkCollision('x'); // Проверка столкновений по оси OX
	velocity = Vector2f(0, 0);

	// Обработка прыжка
	if (!onGround)
	{
		velocity += jumpForceNow;

		// Изменение гравитации после отпускания клавиши
		if (jumpForceNow.y < 0 && !jumpBoost)
		{
			jumpForceNow.y *= n;
		}
		else if (jumpForceNow.y >= 0)
		{
			jumpBoost = false;
		}

		// Влияние гравитации
		jumpForceNow += gravity;
	}

	if (velocity.y == 0.0)
	{
		onGround = false;
		jumpForceNow = gravity;
		velocity += jumpForceNow;
	}

	velocity.y *= delta;
	position += velocity;
	this->checkCollision('y'); // Проверка столкновений по оси OY

	position.x += velocity.x * delta;

	sprite.setPosition(position);

	// Перемещение прямоугольников
	baseRect.left = position.x;
	baseRect.top = position.y;
	additionalRect.left = position.x + shiftWidth;
	additionalRect.top = position.y + shiftHeight;
	showRect.setPosition(position);
	showAdditionalRect.setPosition(Vector2f(additionalRect.left, additionalRect.top));

	// Проверка давления
	if ((sidePressure[0] > 0 && sidePressure[1] > 0) ||
		(sidePressure[2] > 0 && sidePressure[3] > 0))
	{
		health = 0;
	}
}

void Player::draw(RenderWindow& window)
{
	if (visible)
		window.draw(sprite);

	if (rectanglesVisible)
	{
		window.draw(showRect);
		window.draw(showAdditionalRect);

		if (sidePressure[0] > 0)
		{
			showPressure.setPosition(Vector2f(position.x - 10, position.y + 22));
			window.draw(showPressure);
		}
		if (sidePressure[1] > 0)
		{
			showPressure.setPosition(Vector2f(position.x + baseRect.width - 10, position.y + 22));
			window.draw(showPressure);
		}
		if (sidePressure[2] > 0)
		{
			showPressure.setPosition(Vector2f(position.x + 14, position.y + baseRect.height - 10));
			window.draw(showPressure);
		}
		if (sidePressure[3] > 0)
		{
			showPressure.setPosition(Vector2f(position.x + 14, position.y - 10));
			window.draw(showPressure);
		}
	}

	healthBar.draw(window);
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
	// Предварительное изменение позиции для проверки столкновений
	baseRect.left = position.x;
	baseRect.top = position.y;
	 
	for (MoveObject* moveObject : moveObjects)
	{
		this->checkObject(moveObject, axis);
	}

	for (int x = (int)(position.x) / 64; x <= ((int)(position.x) + baseRect.width) / 64; x++)
	{
		for (int y = (int)baseRect.top / 64; y <= ((int)baseRect.top + baseRect.height) / 64; y++)
		{
			this->checkObject(field[x][y], axis);
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

void Player::setData(vector<vector<BaseObject*>>& field, 
	vector<MoveObject*>& moveObjects)
{
	this->field = field;
	this->moveObjects = moveObjects;
}

void Player::takeDamage(int damage)
{
	if (!immortal)
	{
		health -= damage;
		healthBar.update(health);

		immortal = true;
		immortalTimer = 0;
		visibleCounter = 0;
	}
}

void Player::healing(int healthValue)
{
	health += healthValue;

	healthBar.update(health);
}

void Player::checkObject(BaseObject* object, char axis)
{
	if (object != NULL && !object->isDestroyed())
	{
		objectName = object->getName();

		if (baseRect.intersects(object->getRect()) &&
			(objectName == "wall" || objectName == "selfDestructiveBlock" ||
				objectName == "cannon" || objectName == "jumpBoost" || objectName == "moveWall"))
		{
			if (axis == 'x')
			{
				if (velocity.x > 0)
				{
					if (objectName == "moveWall")
						velocity.x = object->getValue();

					position.x = object->getRect().left - baseRect.width - 0.1;
					sidePressure[1]++;
				}
				else if (velocity.x < 0)
				{
					if (objectName == "moveWall")
						velocity.x = object->getValue();
					
					position.x = object->getRect().left + object->getRect().width + 0.1;
					sidePressure[0]++;
				}
				else if (objectName == "moveWall")
				{
					velocity.x = object->getValue();

					if (object->getValue() > 0)
					{
						position.x = object->getRect().left + object->getRect().width + 0.1;
						sidePressure[0]++;
					}
					else
					{
						position.x = object->getRect().left - baseRect.width - 0.1;
						sidePressure[1]++;
					}
				}
			}
			else if (axis == 'y')
			{ 
				if (velocity.y > 0)
				{
					position.y = object->getRect().top - texture.getSize().y - 0.1;
					if (!jumpBoost)
					{
						onGround = true;
						n = 1;
						jumpForceNow = jumpForce;
						sidePressure[2]++;
					}

					if (objectName == "selfDestructiveBlock")
					{
						object->startProcess();
					}
					else if (objectName == "jumpBoost")
					{
						onGround = false;
						jumpReady = false;
						jumpBoost = true;

						jumpForceNow = jumpForce - Vector2f(0, object->getValue());
					}
					else if (objectName == "moveWall")
					{
						velocity.x = object->getValue();
					}
				}
				else if (velocity.y < 0)
				{
					jumpForceNow.y = 0;
					position.y = object->getRect().top + object->getRect().height + 0.1;
					sidePressure[3]++;
				}
			}
		}

		if (objectName == "platform")
		{
			if (axis == 'y')
			{
				if (velocity.y > 0 && position.y + baseRect.height <= object->getRect().top +
					(int)object->getRect().height
					&& !(((controlType == "joystickX" || controlType == "joystickD") &&
						(Joystick::getAxisPosition(0, Joystick::Y) == 100 ||
							Joystick::getAxisPosition(0, Joystick::PovY) == -100)) ||
						(controlType == "keyboard" && Keyboard::isKeyPressed(Keyboard::S))))
				{
					position.y = object->getRect().top - texture.getSize().y - 0.1;
					if (!jumpBoost)
					{
						onGround = true;
						n = 1;
						jumpForceNow = jumpForce;
					}
				}
			}
		}

		if (additionalRect.intersects(object->getRect()))
		{
			if (objectName == "spikes" && object->getValue() > 0)
			{
				this->takeDamage((int)object->getValue());
			}
			else if (objectName == "killZone")
			{
				health = 0;
			}
			else if (objectName == "spikesTrap")
			{
				object->startProcess();

				if ((int)object->getValue() > 0)
					this->takeDamage(object->getValue());
			}
		}
	}
}

Rect<float> Player::getAdditionalRect()
{
	return additionalRect;
}
