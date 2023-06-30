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
	mainScene.addPlayer(player, Vector2f(4, 8));

	// Walls
	mainScene.addObject(new Wall, Vector2f(2, 7));
	mainScene.addObject(new Wall, Vector2f(2, 8));
	mainScene.addObject(new Wall, Vector2f(2, 9));
	mainScene.addObject(new Wall, Vector2f(3, 9));
	mainScene.addObject(new Wall, Vector2f(4, 9));
	mainScene.addObject(new Wall, Vector2f(5, 9));
	mainScene.addObject(new Wall, Vector2f(5, 10));
	mainScene.addObject(new Wall, Vector2f(6, 10));
	mainScene.addObject(new Wall, Vector2f(7, 10));
	mainScene.addObject(new Wall, Vector2f(7, 9));
	mainScene.addObject(new Wall, Vector2f(8, 9));
	mainScene.addObject(new Wall, Vector2f(9, 9));
	mainScene.addObject(new Wall, Vector2f(9, 10));
	mainScene.addObject(new Wall, Vector2f(10, 10));
	mainScene.addObject(new Wall, Vector2f(11, 10));
	mainScene.addObject(new Wall, Vector2f(12, 10));
	mainScene.addObject(new Wall, Vector2f(12, 9));
	mainScene.addObject(new Wall, Vector2f(13, 9));
	mainScene.addObject(new Wall, Vector2f(14, 9));
	mainScene.addObject(new Wall, Vector2f(15, 9));
	mainScene.addObject(new Wall, Vector2f(16, 9));
	mainScene.addObject(new Wall, Vector2f(17, 9));
	mainScene.addObject(new Wall, Vector2f(18, 9));
	mainScene.addObject(new Wall, Vector2f(18, 8));
	mainScene.addObject(new Wall, Vector2f(18, 7));
	mainScene.addObject(new Wall, Vector2f(18, 6));
	mainScene.addObject(new Wall, Vector2f(19, 6));
	mainScene.addObject(new Wall, Vector2f(20, 6));
	mainScene.addObject(new Wall, Vector2f(21, 6));
	mainScene.addObject(new Wall, Vector2f(21, 5));
	mainScene.addObject(new Wall, Vector2f(21, 4));

	mainScene.addObject(new Wall, Vector2f(13, 8));
	mainScene.addObject(new Wall, Vector2f(15, 7));
	mainScene.addObject(new Wall, Vector2f(16, 7));

	// Spikes
	mainScene.addObject(new Spikes("down"), Vector2f(6, 9));
	mainScene.addObject(new Spikes("down"), Vector2f(10, 9));
	mainScene.addObject(new Spikes("down"), Vector2f(11, 9));

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
