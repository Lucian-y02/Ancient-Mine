#include "Scene.h"

#include <iostream>

using namespace std;
using namespace sf;

Scene::Scene()
{
	window.create(VideoMode::getDesktopMode(), "Abandoned", Style::Fullscreen);
	window.setFramerateLimit(fpsLimit);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	field.resize(fieldWidth);

	for (size_t x = 0; x < fieldWidth; x++)
	{
		field[x].resize(fieldHeigth);
	}
}

void Scene::update(double delta)
{
	this->checkEvents();

	for (size_t i = 0; i < players.size(); i++)
	{
		if (!players[i]->isAlive())
			isGameRunning = false;
	}

	for (size_t x = 0; x < fieldWidth; x++)
	{
		for (size_t y = 0; y < fieldHeigth; y++)
		{
			if (field[x][y] != NULL)
	field[x][y]->update(delta);
		}
	}
}

void Scene::draw()
{
	window.clear(Color(170, 170, 170));

	for (size_t x = 0; x < fieldWidth; x++)
	{
		for (size_t y = 0; y < fieldHeigth; y++)
		{
			if (field[x][y] != NULL)
				field[x][y]->draw(window);
		}
	}

	window.display();
}

void Scene::addObject(BaseObject* object, Vector2f position)
{
	object->setPosition(position);
	field[position.x][position.y] = object;
}

void Scene::addPlayer(Player* player, Vector2f position)
{
	this->addObject(player, position);
	players.push_back(player);
}

void Scene::deleteObject(Vector2f position)
{
	if (field[position.x][position.y] != NULL)
	{
		delete field[position.x][position.y];
		field[position.x][position.y] = NULL;
	}
}

void Scene::checkEvents()
{
	while (window.pollEvent(mainEvent))
	{
		if (mainEvent.type == Event::Closed ||
			(mainEvent.type == Event::KeyPressed && mainEvent.key.code == Keyboard::Delete))
		{
			isGameRunning = false;
		}
		if (mainEvent.type == Event::KeyReleased && mainEvent.key.code == Keyboard::F1)
		{
			for (size_t x = 0; x < fieldWidth; x++)
			{
				for (size_t y = 0; y < fieldHeigth; y++)
				{
					if (field[x][y] != NULL)
						field[x][y]->showRectangles();
				}
			}
		}
	}
}

bool Scene::isPerformed()
{
	return isGameRunning;
}

vector<vector<BaseObject*>>& Scene::getField()
{
	return field;
}

Scene::~Scene()
{
	for (size_t x = 0; x < fieldWidth; x++)
	{
		for (size_t y = 0; y < fieldHeigth; y++)
		{
			if (field[x][y] != NULL)
				delete field[x][y];
		}
	}
}
