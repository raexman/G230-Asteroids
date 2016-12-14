//
//  Asteroid.h
//  Asteroids
//
//  Created by Rogelio Espinoza on 12/13/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include "MovingObject.h"

class Asteroid : public MovingObject
{
public:
    int level = 1;
	float collisionStart;
	float collisionCooldown = 2.0f;
    //States;
    void Hit(); //hit by projectile
    void Hurt(){ if(armor > 0) {armor--; }else{ hp--;} }; //hurt
    void Collided(GameObject *other); //collided
    
    //Getters/Setters;
	Vector2f getCenter() { return view.getPosition(); };
    
    //Actions;
    
    //Tructors.
    Asteroid(Vector2f speed, float angle, Vector2f size, RenderWindow *window, BucketGrid *bucket);
    Asteroid(Vector2f speed, Vector2f direction, Vector2f size, RenderWindow *window, BucketGrid *bucket);
    Asteroid(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, RenderWindow *window, BucketGrid *bucket);
    Asteroid(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket);
    ~Asteroid();
    
    void Init();
    void Destroy();
    void Subdivide();

};
