#include "Explosion.h"



Explosion::Explosion(int duration, Vector2f size, RenderWindow *window, BucketGrid *bucket) : GameObject(size, window, bucket)
{
	this->duration = duration;
	explosionStart = currentTime;
}


Explosion::~Explosion()
{
}

void Explosion::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	currentTime += deltaTime;


	Draw();
}

void Explosion::Draw()
{
	this->window->draw(view);
}