#pragma once
#include "MovableGameObject.h"
class Asteroid :
	public MovableGameObject
{
public:
	Asteroid(sf::Vector2f speed, int lives, sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture);
	~Asteroid();
	//void Collided(sf::Vector2f point);
};

