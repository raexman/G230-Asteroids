#pragma once
#include "MovableGameObject.h"
#include "Asteroid.h"
class Ball :
	public MovableGameObject
{
public:
	int lives;
	bool isResting;
	bool isDrilling;
	Ball(sf::Vector2f speed, int lives, sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture);
	~Ball();
	void Init();
	void Update(float deltaTime);
	bool CheckCollisionWith(Asteroid *other, bool drillable = false);
	void Collided();
	void Hurt(int damage = 1);
	int GetLives();
};

