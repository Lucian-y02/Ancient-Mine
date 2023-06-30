#include "Wall.h"

using namespace std;
using namespace sf;

Wall::Wall() : BaseObject("wall", "Textures/orangeBox.png") 
{
	showRect.setFillColor(Color(100, 100, 100));
};

Wall::Wall(Vector2f position) : BaseObject(position, "wall", "Textures/orangeBox.png") 
{
	showRect.setFillColor(Color(100, 100, 100));
}
