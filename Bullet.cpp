//
//  Bullet.cpp
//  Asteroids
//
//  Created by Rogelio Espinoza on 12/13/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#include "Bullet.h"
#include "BucketGrid.h"
#include "Ship.h"
#include "Asteroid.h"

Bullet::Bullet(Vector2f speed, float angle, Vector2f size, RenderWindow *window, BucketGrid *bucket, Ship *ship):MovingObject(speed,angle,size,window, bucket)
{
	this->ship = ship;
    Init();
}
Bullet::Bullet(Vector2f speed, Vector2f direction, Vector2f size, RenderWindow *window, BucketGrid *bucket, Ship *ship):MovingObject(speed,direction,size,window, bucket)
{
	this->ship = ship;
	Init();
}
Bullet::Bullet(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, RenderWindow *window, BucketGrid *bucket, Ship *ship):MovingObject(speed,direction,size,position,window, bucket)
{
	this->ship = ship;
	Init();
}
Bullet::Bullet(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket, Ship *ship):MovingObject(speed,direction,size,position, texture,window, bucket)
{
	this->ship = ship;
	Init();
}
Bullet::~Bullet()
{
    bucket = NULL;
}

void Bullet::Collided(GameObject *other)
{
    if(other->type == "asteroid")
    {
        //ship->bullets.erase(remove(ship->bullets.begin(), ship->bullets.end(), this));
		Asteroid *target = dynamic_cast<Asteroid*>(other);
		ship->score = target->level * 100;
        isActive = false;
    }
}

void Bullet::Init()
{
    this->type = "bullet";
    birthTime = currentTime;
    
    buffer.loadFromFile("Assets/sounds/bullet.wav");
    sound.setBuffer(buffer);
    sound.play();
}

void Bullet::Update(float deltaTime)
{
    this->deltaTime = deltaTime;
    this->currentTime+=deltaTime;
    
    if(lifeSpan <= (currentTime - birthTime))
    {
        this->isActive = false;
    }
    Move();
    Wrap();
    Draw();
}
