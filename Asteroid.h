#pragma once
#include "MovableGameObject.h"
class Asteroid :
	public MovableGameObject
{
protected:
	int level;
public:
	bool Killed;
	Asteroid(sf::Vector2f speed, int lives, sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture, bool hasWalls, bool isWrapping);
	~Asteroid();
	//void Collided(sf::Vector2f point);
	void Shot();
};

