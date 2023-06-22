#include "Scene.h"

using namespace sf;

void Scene::draw(RenderWindow& window)
{
	for (size_t i = 0; i < field.size(); i++)
	{
		field[i]->draw(window);
	}
}

void Scene::update(double delta)
{
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

void Scene::checkEvents(RenderWindow& window)
{
	while (!window.pollEvent(mainEvent))
	{
		if (mainEvent.type == Event::Closed ||
			(mainEvent.type == Event::KeyPressed && mainEvent.key.code == Keyboard::Key::Delete))
		{
			isPerformed = false;
		}
	}
}

Scene::~Scene()
{
	for (size_t i = 0; i < field.size(); i++)
	{
		delete field[i];
	}
}
