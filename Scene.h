#pragma once

#include "BaseObject.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>

class Scene
{
private:

	sf::Event mainEvent;
	sf::RenderWindow window;
	std::vector<Player*> players;
	std::vector<std::vector<BaseObject*>> field;
	int fpsLimit = 60;
	int fieldWidth = 30;
	int fieldHeigth = 20;
	bool isGameRunning = true;
	bool isFullScreen = true;

public:

	Scene();

	void update(double delta);
	void draw();
	void addObject(BaseObject* object, sf::Vector2f position);
	void addPlayer(Player* player, sf::Vector2f position);
	void deleteObject(sf::Vector2f position);
	void checkEvents();
	bool isPerformed();
	std::vector<std::vector<BaseObject*>>& getField();

	~Scene();
};
