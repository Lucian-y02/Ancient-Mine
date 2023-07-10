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

Player::Player(vector<vector<BaseObject*>>& field, string controlType) :
	BaseObject("player", "Textures/player.png") 
{
	this->controlType = controlType;
	this->field = field;

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

	if (jumpBoost)
	{
		//cout << jumpForceNow.y << "\tonGround: " << onGround << endl;
	}

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

	// Переменещние на движущейся платформе
	position.x += velocity.x * delta;

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
	if (visible)
		window.draw(sprite);

	if (rectanglesVisible)
	{
		window.draw(showRect);
		window.draw(showAdditionalRect);
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
	string objectName;

	// Предварительное изменение позиции для проверки столкновений
	if (axis == 'x')
		baseRect.left = position.x;
	else if (axis == 'y')
		baseRect.top = position.y;

	for (int x = (int)(position.x) / 64; x <= ((int)(position.x) + baseRect.width) / 64; x++)
	{
		for (int y = (int)baseRect.top / 64; y <= ((int)baseRect.top + baseRect.height) / 64; y++)
		{
			if (field[x][y] != NULL && !field[x][y]->isDestroyed())
			{
				objectName = field[x][y]->getName();

				if (baseRect.intersects(field[x][y]->getRect()) && 
					(objectName == "wall" || objectName == "selfDestructiveBlock" ||
					objectName == "cannon" || objectName == "jumpBoost" || objectName == "moveWall"))
				{
					if (axis == 'x')
					{
						if (velocity.x > 0)
						{
							position.x = field[x][y]->getRect().left - texture.getSize().x - 0.1;
						}
						else if (velocity.x < 0)
						{
							position.x = field[x][y]->getRect().left + field[x][y]->getRect().width + 0.1;
						}
					}
					else if (axis == 'y')
					{
						if (velocity.y > 0)
						{
							position.y = field[x][y]->getRect().top - texture.getSize().y - 0.1;
							if (!jumpBoost)
							{
								onGround = true;
								n = 1;
								jumpForceNow = jumpForce;
							}

							if (objectName == "selfDestructiveBlock")
							{
								field[x][y]->startProcess();
							}
							else if (objectName == "jumpBoost")
							{
								onGround = false;
								jumpReady = false;
								jumpBoost = true;

								jumpForceNow = jumpForce - Vector2f(0, field[x][y]->getValue());
							}
							else if (objectName == "moveWall")
							{
								velocity.x += field[x][y]->getValue();
							}
						}
						else if (velocity.y < 0)
						{
							jumpForceNow.y = 0;
							position.y = field[x][y]->getRect().top + field[x][y]->getRect().height + 0.1;
						}
					}
				}

				if (objectName == "platform")
				{
					if (axis == 'y')
					{
						if (velocity.y > 0 && position.y + baseRect.height <= y * 64 + 
							(int)field[x][y]->getRect().height
							&& !(((controlType == "joystickX" || controlType == "joystickD") && 
								(Joystick::getAxisPosition(0, Joystick::Y) == 100 || 
								 Joystick::getAxisPosition(0, Joystick::PovY) == -100)) || 
								(controlType == "keyboard" && Keyboard::isKeyPressed(Keyboard::S))))
						{
							position.y = field[x][y]->getRect().top - texture.getSize().y - 0.1;
							if (!jumpBoost)
							{
								onGround = true;
								n = 1;
								jumpForceNow = jumpForce;
							}
						}
					}
				}

				if (additionalRect.intersects(field[x][y]->getRect()))
				{
					if (objectName == "spikes" && field[x][y] > 0)
					{
						this->takeDamage((int)field[x][y]->getValue());
					}
					else if (objectName == "killZone")
					{
						health = 0;
					}
					else if (objectName == "spikesTrap")
					{
						field[x][y]->startProcess();

						if ((int)field[x][y]->getValue() > 0)
							this->takeDamage(field[x][y]->getValue());
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

Rect<float> Player::getAdditionalRect()
{
	return additionalRect;
}
