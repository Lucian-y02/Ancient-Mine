#include "Scene.h"
#include "Wall.h"
#include "DamageObjects.h"
#include "BaseObject.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

int main()
{
	Scene mainScene;

	// Player
	Player* player = new Player(mainScene.getField(), "joystickX");
	mainScene.addPlayer(player, Vector2f(9, 3));

	// Walls
	for (size_t x = 0; x < 30; x++)
	{
		mainScene.addObject(new Wall, Vector2f(x, 12));
	}

	mainScene.addObject(new Wall, Vector2f(8, 4));
	mainScene.addObject(new Wall, Vector2f(9, 4));
	mainScene.addObject(new Wall, Vector2f(10, 4));

	mainScene.addObject(new Wall, Vector2f(3, 7));
	mainScene.addObject(new Wall, Vector2f(3, 8));
	mainScene.addObject(new Wall, Vector2f(5, 6));
	mainScene.addObject(new Wall, Vector2f(6, 6));
	mainScene.addObject(new Wall, Vector2f(4, 8));
	mainScene.addObject(new Wall, Vector2f(5, 8));
	mainScene.addObject(new Wall, Vector2f(6, 8));
	mainScene.addObject(new Wall, Vector2f(7, 8));

	mainScene.addObject(new Wall, Vector2f(9, 8));
	mainScene.addObject(new Wall, Vector2f(10, 8));

	mainScene.addObject(new Wall, Vector2f(12, 7));
	mainScene.addObject(new Wall, Vector2f(12, 8));
	mainScene.addObject(new Wall, Vector2f(13, 8));
	mainScene.addObject(new Wall, Vector2f(14, 8));
	mainScene.addObject(new Wall, Vector2f(15, 8));
	mainScene.addObject(new Wall, Vector2f(15, 7));
	mainScene.addObject(new Wall, Vector2f(15, 6));
	mainScene.addObject(new Wall, Vector2f(16, 6));

	// Spikes
	mainScene.addObject(new Spikes("down"), Vector2f(10, 7));
	mainScene.addObject(new Spikes("down"), Vector2f(5, 5));
	mainScene.addObject(new Spikes("down"), Vector2f(16, 5));

	player->setField(mainScene.getField());

	Clock mainClock;
	double delta;

	while (mainScene.isPerformed())
	{
		delta = mainClock.getElapsedTime().asMilliseconds() / 1000.0;
		mainClock.restart();

		mainScene.update(delta);
		mainScene.draw();
	}
}
