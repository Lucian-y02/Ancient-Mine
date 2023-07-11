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

	// Обновление гроков
	for (size_t i = 0; i < players.size(); i++)
	{
		if (!players[i]->isAlive())
			isGameRunning = false;
		else
			players[i]->update(delta);
	}

	// Обновление основных объектов
	for (size_t x = 0; x < fieldWidth; x++)
	{
		for (size_t y = 0; y < fieldHeigth; y++)
		{
			if (field[x][y] != NULL)
			{
				if (field[x][y]->isDestroyed())
				{
					delete field[x][y];
					field[x][y] = NULL;
				}
				else
					field[x][y]->update(delta);
			}
		}
	}

	// Обновление движущихся объектов
	for (MoveObject* moveObject : moveObjects)
	{
		moveObject->update(delta);
	}
}

void Scene::draw()
{
	window.clear(Color(170, 170, 170));

	// Отрисовка основных объектов
	for (size_t x = 0; x < fieldWidth; x++)
	{
		for (size_t y = 0; y < fieldHeigth; y++)
		{
			if (field[x][y] != NULL)
				field[x][y]->draw(window);
		}
	}

	// Отрисовка игроков
	for (Player* player : players)
	{
		player->draw(window);
	}

	// Отрисовка движущихся объектов
	for (MoveObject* moveObject : moveObjects)
	{
		moveObject->draw(window);
	}

	// Отрисовка сетки
	if (gridDraw)
	{
		RectangleShape grid;
		grid.setFillColor(Color(75, 75, 75, 150));
		grid.setSize(Vector2f(window.getSize().x, 1));
		for (size_t i = 0; i < fieldHeigth; i++)
		{
			grid.setPosition(Vector2f(0, 64.0 * i));
			window.draw(grid);
		}
		grid.setSize(Vector2f(1, window.getSize().y));
		for (size_t i = 0; i < fieldWidth; i++)
		{
			grid.setPosition(Vector2f(64.0 * i, 0));
			window.draw(grid);
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
	player->setPosition(position);
	players.push_back(player);
}

void Scene::addMoveObject(MoveObject* object, Vector2f position)
{
	object->setPosition(position);
	moveObjects.push_back(object);
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
		if (mainEvent.type == Event::Closed)
		{
			isGameRunning = false;
		}
		if (mainEvent.type == Event::KeyReleased)
		{
			if (mainEvent.key.code == Keyboard::F1)
			{
				for (size_t x = 0; x < fieldWidth; x++)
				{
					for (size_t y = 0; y < fieldHeigth; y++)
					{
						if (field[x][y] != NULL)
							field[x][y]->showRectangles();
					}
				}

				for (Player* player : players)
				{
					player->showRectangles();
				}

				for (MoveObject* moveObject : moveObjects)
				{
					moveObject->showRectangles();
				}
			}

			if (mainEvent.key.code == Keyboard::Delete)
				isGameRunning = false;

			if (mainEvent.key.code == Keyboard::F2)
			{
				gridDraw = !gridDraw;
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

vector<Player*>& Scene::getPlaeyrs()
{
	return players;
}

vector<MoveObject*>& Scene::getMoveObjects()
{
	return moveObjects;
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
