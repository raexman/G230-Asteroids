//
//  ControlledObject.h
//  Asteroids
//
//  Created by Rogelio Espinoza on 12/13/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "MovingObject.h"

using namespace sf;
class ControlledObject : public MovingObject
{
public:
    Keyboard::Key up = Keyboard::Key::Up;
    Keyboard::Key down = Keyboard::Key::Down;
    Keyboard::Key left = Keyboard::Key::Left;
    Keyboard::Key right = Keyboard::Key::Right;
    Keyboard::Key primary = Keyboard::Key::Space;
    Keyboard::Key secondary =  Keyboard::Key::LShift;
    
    bool Control();
    virtual void Up() = 0;
    virtual void Down() = 0;
    virtual void Left() = 0;
    virtual void Right() = 0;
    virtual void Primary() = 0;
    virtual void Secondary() = 0;
    
    virtual void Update(float deltaTime);
    
    //Tructors.
    ControlledObject(Vector2f speed, float angle, Vector2f size, RenderWindow *window, BucketGrid *bucket);
    ControlledObject(Vector2f speed, Vector2f direction, Vector2f size, RenderWindow *window, BucketGrid *bucket);
    ControlledObject(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, RenderWindow *window, BucketGrid *bucket);
    ControlledObject(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket);
    ControlledObject(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right, Keyboard::Key primary, Keyboard::Key secondary, Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket);
    ~ControlledObject();
    void Init();
};
