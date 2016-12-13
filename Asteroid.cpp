#include "Asteroid.h"



Asteroid::Asteroid(sf::Vector2f speed, int lives, sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture, bool hasWalls, bool isWrapping) :MovableGameObject(size, position, window, texture, hasWalls, isWrapping)
{
	this->speed = speed;
}


Asteroid::~Asteroid()
{
}

void Asteroid::Shot()
{
	Killed = true;
	//Subdivide;
	if (level < 3)
	{

	}
	//Destroy;
}