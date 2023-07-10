#include "Scene.h"
#include "Wall.h"
#include "DamageObjects.h"
#include "BaseObject.h"
#include "Cannons.h"
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
	mainScene.addPlayer(player, Vector2f(3, 2));

	// Another objects
	mainScene.addObject(new Platform, Vector2f(3, 3));
	mainScene.addObject(new Wall, Vector2f(4, 9));
	mainScene.addObject(new Wall, Vector2f(5, 9));
	mainScene.addObject(new Wall, Vector2f(6, 9));
	mainScene.addObject(new JumpBoost, Vector2f(2, 11));
	mainScene.addObject(new Platform, Vector2f(3, 11));
	mainScene.addObject(new Platform, Vector2f(4, 11));
	mainScene.addObject(new Platform, Vector2f(5, 11));
	mainScene.addObject(new Platform, Vector2f(6, 11));
	mainScene.addObject(new Platform, Vector2f(7, 11));
	mainScene.addObject(new Platform, Vector2f(8, 11));
	
	MoveWall* moveWall = new MoveWall("right");
	mainScene.addObject(moveWall, Vector2f(7, 9));
	moveWall->addMarker(Vector2f(7, 9), "left", "right");
	moveWall->addMarker(Vector2f(8, 9), "right", "left");

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
