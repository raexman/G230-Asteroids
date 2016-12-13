#include "Ball.h"



Ball::Ball(sf::Vector2f speed, int lives, sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture):MovableGameObject(size, position, window, texture)
{
	this->speed = speed;
	this->HP = lives;
	SetWalls(true, true, false, true);
	Init();
}
void Ball::Init()
{
	this->view.setTexture(&texture);
}

void Ball::Update(float deltaTime)
{
	this->deltaTime = deltaTime;

	if (!isActive) return;

	if (isMoving)
	{
		Move();
	}
	if (GetPosition().y > window->getSize().y)
	{
		//Reset ball;
		isResting = true;
		Hurt();
		if (Dead()){
			//End game.
			isActive = false;
		}
		else
		{
			std::string soundFx = "falling.wav";
			buffer.loadFromFile(soundFx);
			sound.setBuffer(buffer);
			sound.play();
		}
	}

	Draw();

}

void Ball::Hurt(int damage)
{
	HP -= damage;
}

Ball::~Ball()
{
}
bool Ball::CheckCollisionWith(Asteroid *other, bool drillable)
{

	sf::Vector2f pointOfContact = GetPointOfContact(other);
	if (!inContact)
	{
		if (pointOfContact.x >= -1 && pointOfContact.x <= 1 && pointOfContact.y >= -1 && pointOfContact.y <= 1)
		{

			other->Shot();
			this->Collided();
			inContact = true;

			return true;
		}
	}
	else
	{
		if (pointOfContact.x < -1 || pointOfContact.x > 1 || pointOfContact.y < -1 || pointOfContact.y > 1)
		{
			inContact = false;
		}
	}

	return false;
}

void Ball::Collided()
{
	HP = 0;
}

int Ball::GetLives()
{
	return HP;
}