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
	Player* player = new Player(mainScene.getField(), mainScene.getMoveObjects(), "joystickX");
	mainScene.addPlayer(player, Vector2f(5, 8));

	// Another objects
	mainScene.addObject(new Wall, Vector2f(2, 7));
	mainScene.addObject(new Wall, Vector2f(2, 8));
	mainScene.addObject(new Wall, Vector2f(2, 9));
	mainScene.addObject(new Wall, Vector2f(3, 9));
	mainScene.addObject(new Wall, Vector2f(4, 9));
	mainScene.addObject(new Wall, Vector2f(4, 7));
	mainScene.addObject(new Wall, Vector2f(5, 9));
	mainScene.addObject(new Wall, Vector2f(6, 9));
	mainScene.addObject(new Wall, Vector2f(7, 9));
	mainScene.addObject(new Wall, Vector2f(8, 9));
	mainScene.addObject(new Wall, Vector2f(9, 9));
	mainScene.addObject(new Wall, Vector2f(10, 9));
	mainScene.addObject(new Wall, Vector2f(11, 9));
	mainScene.addObject(new Wall, Vector2f(12, 9));
	mainScene.addObject(new Wall, Vector2f(13, 9));
	mainScene.addObject(new Wall, Vector2f(13, 8));
	mainScene.addObject(new Wall, Vector2f(14, 9));
	mainScene.addObject(new Wall, Vector2f(15, 9));
	
	MoveWall* moveWall = new MoveWall("right");
	mainScene.addMoveObject(moveWall, Vector2f(7, 8));
	moveWall->addMarker(Vector2f(7, 8), "left", "right");
	moveWall->addMarker(Vector2f(10, 8), "right", "left");

	moveWall = new MoveWall("left");
	mainScene.addMoveObject(moveWall, Vector2f(8, 7));
	moveWall->addMarker(Vector2f(6, 7), "left", "right");
	moveWall->addMarker(Vector2f(11, 7), "right", "left");

	player->setData(mainScene.getField(), mainScene.getMoveObjects());

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
