//
//  ControlledObject.cpp
//  Asteroids
//
//  Created by Rogelio Espinoza on 12/13/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#include "ControlledObject.h"
#include "BucketGrid.h"

using namespace sf;

ControlledObject::ControlledObject(Vector2f speed, float angle, Vector2f size, RenderWindow *window, BucketGrid *bucket) : MovingObject(speed, angle, size, window, bucket)
{
    Init();
}
ControlledObject::ControlledObject(Vector2f speed, Vector2f direction, Vector2f size, RenderWindow *window, BucketGrid *bucket) : MovingObject(speed, direction, size, window, bucket)
{
    Init();
}
ControlledObject::ControlledObject(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, RenderWindow *window, BucketGrid *bucket) : MovingObject(speed, direction, size, position, window, bucket)
{
    Init();
}
ControlledObject::ControlledObject(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket) : MovingObject(speed, direction, size, position, texture, window, bucket)
{
    Init();
}
ControlledObject::ControlledObject(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right, Keyboard::Key primary, Keyboard::Key secondary, Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket) : MovingObject(speed, direction, size, position, texture, window, bucket)
{
    this->up = up;
    this->down = down;
    this->left = left;
    this->right = right;
    this->primary = primary;
    this->secondary = secondary;

    Init();
}
ControlledObject::~ControlledObject()
{
    
}

bool ControlledObject::Control()
{
    if(Keyboard::isKeyPressed(up))
    {
        Up();
    }
    if(Keyboard::isKeyPressed(down))
    {
        Down();
    }
    if(Keyboard::isKeyPressed(left))
    {
        Left();
    }
    if(Keyboard::isKeyPressed(right))
    {
        Right();
    }
    if(Keyboard::isKeyPressed(primary))
    {
        Primary();
    }
    if(Keyboard::isKeyPressed(secondary))
    {
		Secondary();
    }

	return false;
}

void ControlledObject::Init()
{
    if(!up)         up =        Keyboard::Key::Up;
    if(!down)       down =      Keyboard::Key::Down;
    if(!left)       left =      Keyboard::Key::Left;
    if(!right)      right =     Keyboard::Key::Right;
    if(!primary)    primary =   Keyboard::Key::Space;
    if(!secondary)  secondary = Keyboard::Key::LShift;
}

void ControlledObject::Update(float deltaTime)
{
    //std::cout << "UPDATE MO" << std::endl;
    this->deltaTime = deltaTime;
    Control();
    Move();
    Wrap();
    Draw();
}
