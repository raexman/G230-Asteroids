//
//  Asteroid.cpp
//  Asteroids
//
//  Created by Rogelio Espinoza on 12/13/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#include "Asteroid.h"
#include "BucketGrid.h"
#include "PowerUp.h"

using namespace sf;

Asteroid::Asteroid(Vector2f speed, float angle, Vector2f size, RenderWindow *window, BucketGrid *bucket):MovingObject(speed, angle, size, window, bucket)
{
    this->type = "asteroid";
    Init();
}
Asteroid::Asteroid(Vector2f speed, Vector2f direction, Vector2f size, RenderWindow *window, BucketGrid *bucket):MovingObject(speed, direction, size, window,bucket)
{
    this->type = "asteroid";
    Init();
}
Asteroid::Asteroid(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, RenderWindow *window, BucketGrid *bucket):MovingObject(speed,direction,size,position,window,bucket)
{
    this->type = "asteroid";
    Init();
}

Asteroid::Asteroid(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket):MovingObject(speed,direction,size,position,texture,window,bucket)
{
    this->type = "asteroid";
    Init();
}

Asteroid::~Asteroid()
{
    
}

void Asteroid::Init()
{
    texture.loadFromFile("Assets/images/asteroid.png");
    view.setTexture(&texture);
}

void Asteroid::Hit()
{
    this->Hurt();
    std::cout << "HP: " << hp << std::endl;
    if(hp <= 0)
    {
        Destroy();
    }
}

void Asteroid::Collided(GameObject *other)
{
    if(other->type == "asteroid")
    {
		if (collisionCooldown <= currentTime - collisionStart)
		{
			Vector2f distance;

			direction.x *= -1;
			direction.y *= -1;

			this->view.move(direction.x * 5, direction.y * 5);
			collisionStart = currentTime;
		}
    }
    
    else if(other->type == "bullet")
    {
        this->Hit();
    }
    
    else if(other->type == "ship")
    {
    }
    
   // std::cout << this->type << " collided with " << other->type << std::endl;
}

void Asteroid::Destroy()
{
    //std::cout << "DESTROY!" << std::endl;
    Subdivide();
    this->isActive = false;
	bucket->Pop(this);
}

void Asteroid::Subdivide()
{
    if(level > 2) return;
    //float currentMagnitude = sqrtf( pow(direction.x, 2.0f) + pow(direction.y, 2.0f) );
    float currentAngle = atanf(direction.y / direction.x);

    level++;
    
    for(int i = 0; i < 2; i++)
    {
		bool hasArmor = (rand() % 5) < 1;

        Asteroid *childAsteroid = new Asteroid(Vector2f(speed.x * 2, speed.y * 2), currentAngle + 135 * i, Vector2f(size.x*0.66f, size.y*0.66f), window, bucket);
        childAsteroid->level = level;
        childAsteroid->view.setPosition(this->view.getPosition());
		childAsteroid->armor = hasArmor ? 2 : 0;
        bucket->Push(childAsteroid);
    }

	if (rand() % 3 < 1)
	{
		PowerUp *powerUp = new PowerUp(rand() % 4, Vector2f(20,20), window, bucket);
		powerUp->view.setPosition(this->view.getPosition());
		powerUp->type = "powerup";
		bucket->Push(powerUp);

	}


}
