#pragma once

#include "BaseObject.h"
#include "SFML/Graphics.hpp"
#include <vector>

class Scene
{
private:

	std::vector<BaseObject*> field;
	sf::Event mainEvent;
	bool isPerformed = true;

public:

	Scene() = default;

	void draw(sf::RenderWindow& window);
	void update(double delta);
	void addObject(BaseObject* newOjbect);
	void deleteObject(int index);
	void checkEvents(sf::RenderWindow& window);

	~Scene();
};
