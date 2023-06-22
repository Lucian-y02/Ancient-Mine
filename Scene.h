#pragma once

#include "BaseObject.h"
#include "SFML/Graphics.hpp"
#include <vector>

class Scene
{
private:

	sf::RenderWindow window;
	std::vector<BaseObject*> field;
	sf::Event mainEvent;
	bool isGameRunning = true;
	int fps = 60;

public:

	Scene();

	void draw();
	void update(double delta);
	void addObject(BaseObject* newOjbect);
	void deleteObject(int index);
	void checkEvents();
	bool isPerformed();

	~Scene();
};
