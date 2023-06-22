#include "Scene.h"

using namespace sf;

Scene::Scene()
{
	window.create(VideoMode::getDesktopMode(), "AncientMine", Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);
}

void Scene::draw()
{
	window.clear(Color(100, 100, 100));

	for (size_t i = 0; i < field.size(); i++)
	{
		field[i]->draw(window);
	}
}

void Scene::update(double delta)
{
	this->checkEvents();

	for (size_t i = 0; i < field.size(); i++)
	{
		field[i]->update(delta);
	}
}

void Scene::addObject(BaseObject* newObject)
{
	field.push_back(newObject);
}

void Scene::deleteObject(int index)
{
	field.erase(field.begin() + index);
}

void Scene::checkEvents()
{
	while (!window.pollEvent(mainEvent))
	{
		if (mainEvent.type == Event::Closed ||
			(mainEvent.type == Event::KeyPressed && mainEvent.key.code == Keyboard::Key::Delete))
		{
			isGameRunning = false;
		}
	}
}

bool Scene::isPerformed()
{
	return isGameRunning;
}

Scene::~Scene()
{
	for (size_t i = 0; i < field.size(); i++)
	{
		delete field[i];
	}
}
