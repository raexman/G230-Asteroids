//
//  MovingObject.h
//  Asteroids
//
//  Created by Rogelio Espinoza on 12/13/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include <math.h>
#include "GameObject.h"

using namespace sf;

class MovingObject : public GameObject
{
public:
    
    //Basic;
    float angle;
    Vector2f direction;
    Vector2f speed;
    Vector2f acceleration;
    
    //Behaviours;
    virtual Vector2f Move();
    virtual void Wrap();

    //Render.
    void Update(float deltaTime);
    
    //Tructors.
    MovingObject(Vector2f speed, float angle, Vector2f size, RenderWindow *window, BucketGrid *bucket);
    MovingObject(Vector2f speed, Vector2f direction, Vector2f size, RenderWindow *window, BucketGrid *bucket);
    MovingObject(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, RenderWindow *window, BucketGrid *bucket);
    MovingObject(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket);
    ~MovingObject();
    
    void Init(Vector2f speed, Vector2f direction);

};
