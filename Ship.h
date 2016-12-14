//
//  Ship.h
//  Asteroids
//
//  Created by Rogelio Espinoza on 12/13/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "ControlledObject.h"
#include "Bullet.h"
#include "PowerUp.h"

using namespace sf;

class Ship : public ControlledObject
{
public:
    float friction = 50;
    float rotationSpeed = 200;
    int hp = 3;
	int score;
    
    int bombs;
    
    std::vector<Bullet*> bullets;
    
    int bulletsPerShot = 1;
    float rateOfFire = 0.05f;
    float shotCooldown = 0.25f;
    float lastShot;
    float lastBullet;
    float bulletsShot;
    
    //Flags
    bool hasBurstShot; //3
    bool hasTrishot; //3 + rotation
    bool hasBomb(){ return bombs > 0; };
    bool isShooting;
    
    //States;
	void Hurt() { if (isInvulnerable()) return; if (armor > 0) { armor--; } else { hp--; } }; //hurt
    void Hit(){ std::cout << type << " was hit!" << std::endl; Hurt(); if(hp <= 0) isActive = false; Reset(); }; //hit by projectile
    void Collided(GameObject *other); //collided
    
    //Getters/Setters;
    Vector2f getCenter(){ return view.getPosition(); };
    
    //Actions;
    Vector2f Move();
    void ShootBomb();
	void ResetAmmo();
    void SetBurst();
    void SetTrishot();
    void Shoot();
    void Shooting();
    
    //Controls.
    void Up();
    void Down();
    void Left();
    void Right();
    void Primary();
    void Secondary();
    
    //Tructors.
    Ship(Vector2f speed, float angle, Vector2f size, RenderWindow *window, BucketGrid *bucket);
    Ship(Vector2f speed, Vector2f direction, Vector2f size, RenderWindow *window, BucketGrid *bucket);
    Ship(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, RenderWindow *window, BucketGrid *bucket);
    Ship(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket);
    Ship(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right, Keyboard::Key primary, Keyboard::Key secondary, Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket);
    ~Ship();
    void Init();
    void Update(float deltaTime);
    void Reset();
	void GetPowerUp(PowerUp::PowerType power);
};
