//
//  MovingObject.cpp
//  Asteroids
//
//  Created by Rogelio Espinoza on 12/13/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#include "MovingObject.h"
using namespace sf;
MovingObject::MovingObject(Vector2f speed, float angle, Vector2f size, RenderWindow *window, BucketGrid *bucket):GameObject(size, window, bucket)
{
    float rotationRadians = angle * PI / 180;
    Vector2f direction(cosf(rotationRadians), sinf(rotationRadians));
    
    Init(speed, direction);
}
MovingObject::MovingObject(Vector2f speed, Vector2f direction, Vector2f size, RenderWindow *window, BucketGrid *bucket):GameObject(size, window, bucket)
{
    Init(speed, direction);
}
MovingObject::MovingObject(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, RenderWindow *window, BucketGrid *bucket):GameObject(size,position,window, bucket)
{
    Init(speed, direction);
}

MovingObject::MovingObject(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket):GameObject(size,position,texture,window, bucket)
{
    Init(speed, direction);
}

MovingObject::~MovingObject()
{
}

void MovingObject::Init(Vector2f speed, Vector2f direction)
{
    this->type = "movobj";
    this->speed = speed;
    this->direction = direction;
}

//Render.
void MovingObject::Update(float deltaTime)
{
    
    //std::cout << "UPDATE MO" << std::endl;
    this->deltaTime = deltaTime;
	currentTime += deltaTime;

    Move();
    Wrap();
    Draw();
}

Vector2f MovingObject::Move()
{
    view.move(speed.x * direction.x * deltaTime, speed.y * direction.y * deltaTime);

	return view.getPosition();
}

void MovingObject::Wrap()
{
    if (view.getPosition().x + view.getRadius() < 0)
    {
        view.setPosition(window->getSize().x, view.getPosition().y);
    }
    else if (view.getPosition().x > window->getSize().x)
    {
        view.setPosition(0, view.getPosition().y);
    }
    
    if (view.getPosition().y + view.getRadius() < 0)
    {
        view.setPosition(view.getPosition().x, window->getSize().y);
    }
    else if (view.getPosition().y > window->getSize().y)
    {
        view.setPosition(view.getPosition().x, 0);
    }
}
