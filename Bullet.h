//
//  Bullet.h
//  Asteroids
//
//  Created by Rogelio Espinoza on 12/13/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "MovingObject.h"

class Ship;

class Bullet : public MovingObject
{
public:
	Ship *ship;
    float lifeSpan = 3;
    float birthTime;
    //States;
    void Hurt(){ if(armor > 0) armor--; else hp--; }; //hurt
    void Hit(){ std::cout << type << " was hit!" << std::endl; Hurt(); if(hp <= 0) isActive = false; }; //hit by projectile
    void Collided(GameObject *other); //collided
    
    //Getters/Setters;
	Vector2f getCenter() { return view.getPosition(); };
    
    //Tructors.
    Bullet(Vector2f speed, float angle, Vector2f size, RenderWindow *window, BucketGrid *bucket, Ship *ship);
    Bullet(Vector2f speed, Vector2f direction, Vector2f size, RenderWindow *window, BucketGrid *bucket, Ship *ship);
    Bullet(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, RenderWindow *window, BucketGrid *bucket, Ship *ship);
    Bullet(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket, Ship *ship);
    ~Bullet();
    void Init();
    void Update(float deltaTime);
};
