#include "PowerUp.h"


PowerUp::PowerUp(int power, Vector2f size, RenderWindow *window, BucketGrid *bucket) : GameObject(size, window, bucket)
{
	this->type = "powerup";
	this->power = static_cast<PowerType>(power);
}


PowerUp::~PowerUp()
{
}

void PowerUp::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	Draw();
}

void PowerUp::Draw()
{
	this->window->draw(view);
}
