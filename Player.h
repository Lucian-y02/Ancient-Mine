#pragma once

#include "BaseObject.h"
#include "SFML/Graphics.hpp"
#include <map>
#include <string>
#include <vector>

class Player: public BaseObject
{
private:
	
	// Прямоугольники
	sf::RectangleShape showRect;
	sf::Rect<float> additionalRect;
	float shiftWidth = 7; // Смещение дополнительного прямоугольника по оси OY
	float shiftHeight = 16; // Смещение дополнительного прямоугольника по оси OX
	sf::RectangleShape showAdditionalRect;

	std::vector<std::vector<BaseObject*>> field;

	std::string controlType = "keyboard";

	double speed = 190;
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	sf::Vector2f jumpForce = sf::Vector2f(0, -600);
	sf::Vector2f jumpForceNow = jumpForce;
	sf::Vector2f gravity = sf::Vector2f(0, 30);
	double n = 1;
	bool onGround = true;
	bool jumpReady = true;
	bool immortal = false;
	bool rectanglesVisible = false;
	int health = 10;
	
public:

	Player(std::vector<std::vector<BaseObject*>>& field, std::string controlType = "keyboard");
	Player(sf::Vector2f position, std::vector<std::vector<BaseObject*>>& field,
		std::string controlType = "keyboard");

	void update(double delta) override;
	void draw(sf::RenderWindow& window) override;
	void setPosition(sf::Vector2f newPosition) override;
	void setField(std::vector<std::vector<BaseObject*>>& field);
	void checkPressedKeyboard();
	void checkPressedJoystickX();
	void checkPressedJoystickD();
	void setEnableImmortality(bool value);
	bool isAlive();
	void checkCollision(char axis);
	void showRectangles();
};
