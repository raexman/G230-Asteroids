#include "PowerUp.h"
#include "BucketGrid.h"

PowerUp::PowerUp(int power, Vector2f size, RenderWindow *window, BucketGrid *bucket) : GameObject(size, window, bucket)
{
	this->power = static_cast<PowerType>(power);
	Init();
}


PowerUp::~PowerUp()
{
}

void PowerUp::Init()
{
	this->type = "powerup";
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

void PowerUp::Collided(GameObject *other)
{
	if (other->type == "ship")
	{ 
		bucket->Pop(this);
	}
}