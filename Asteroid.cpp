#include "Asteroid.h"



Asteroid::Asteroid(sf::Vector2f speed, int lives, sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture) :MovableGameObject(size, position, window, texture)
{
	this->speed = speed;
}


Asteroid::~Asteroid()
{
}

//void Asteroid::Collided(sf::Vector2f point)
//{
//	//ChangeDirection(true, true);
//}