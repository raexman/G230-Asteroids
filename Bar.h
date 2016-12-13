#pragma once
#include "MovableGameObject.h"
#include "Ball.h"

class Bar :
	public MovableGameObject
{
protected:
	const float PI = 3.14159265359f;
	sf::Vector2f acceleration;


public:
	Ball *bullet;
	Bar(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture);
	~Bar();
	void Update(float deltaTime);
	void Control();
	void Init();
	void Collided(sf::Vector2f point);
	void Move();
};

