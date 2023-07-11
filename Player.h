#pragma once

#include "BaseObject.h"
#include "Wall.h"
#include "SFML/Graphics.hpp"
#include <map>
#include <string>
#include <vector>

class HealthBar
{
private:

	sf::RectangleShape healthPoint;
	int health;

public:

	HealthBar();

	void update(int health);
	void draw(sf::RenderWindow& window);
};


class Player: public BaseObject
{
private:

	// Вспомогательные переменные
	std::string objectName;
	std::vector<int> sidePressure = { 0, 0, 0, 0 }; // { слева, справа, снизу, сверху }
	sf::RectangleShape showPressure;

	// Прямоугольники
	sf::RectangleShape showAdditionalRect;
	sf::Rect<float> additionalRect;
	float shiftWidth = 7; // Смещение дополнительного прямоугольника по оси OY
	float shiftHeight = 6; // Смещение дополнительного прямоугольника по оси OX

	std::vector<std::vector<BaseObject*>> field;
	std::vector<MoveObject*> moveObjects;

	std::string controlType = "keyboard";

	double speed = 190;
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	sf::Vector2f jumpForce = sf::Vector2f(0, -600);
	sf::Vector2f jumpForceNow = jumpForce;
	sf::Vector2f gravity = sf::Vector2f(0, 30);
	double n = 1;
	bool onGround = true;
	bool jumpReady = true;
	bool jumpBoost = false;
	
	float immortalTimer = 0.0;
	float immortalCoolDown = 2.0;
	bool immortal = false;
	bool visible = true;
	int visibleCounter = 0;
	int health = 5;
	HealthBar healthBar;
	
public:

	Player(std::vector<std::vector<BaseObject*>>& field, 
		std::vector<MoveObject*>& moveObjects,
		std::string controlType = "keyboard");
	Player(sf::Vector2f position, std::vector<std::vector<BaseObject*>>& field,
		std::string controlType = "keyboard");

	void update(double delta) override;
	void draw(sf::RenderWindow& window) override;
	void setPosition(sf::Vector2f newPosition) override;
	void setData(std::vector<std::vector<BaseObject*>>& field, 
		std::vector<MoveObject*>& moveObjects);
	void checkPressedKeyboard();
	void checkPressedJoystickX();
	void checkPressedJoystickD();
	bool isAlive();
	void checkCollision(char axis);
	void takeDamage(int damage);
	void healing(int healthValue);
	void checkObject(BaseObject* object, char axis);
	sf::Rect<float> getAdditionalRect();
};
