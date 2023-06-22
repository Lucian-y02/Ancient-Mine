#include "BaseObject.h"
#include "Scene.h"
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
	cout << "<AncientMine: started>" << endl;

	Scene mainScene;

	Clock mainClock;
	double delta;

	while (mainScene.isPerformed())
	{
		delta = mainClock.getElapsedTime().asMilliseconds();
		mainClock.restart();

		mainScene.update(delta);
		mainScene.draw();
	}

	cout << "<AncientMine: stoped>" << endl;
}
