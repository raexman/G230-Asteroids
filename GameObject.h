//
//  GameObject.h
//  Asteroids
//
//  Created by Rogelio Espinoza on 12/13/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class BucketGrid;

class GameObject
{
public:
    const float PI = 3.14159265359f;
    
    //Time;
    float currentTime;
    float deltaTime;

    //Shape;
    Vector2f size;
    Vector2f position;
    Vector2f rotation;
    CircleShape view;
    Texture texture;
    
    //Basic;
    int armor = 0;
    int hp = 1;
    bool isActive = true;
    std::string type;
    
    //Audiovisual;
    BucketGrid *bucket;
    RenderWindow *window;
    SoundBuffer buffer;
    Sound sound;

    //Invulnerability;
    float invulnerabilityDuration = 5;
    float invulnerabilityStartTime;
    virtual void StartInvulnerability();
    
    //Actions
    virtual bool CheckCollisionWith(GameObject *other);
    float length(Vector2f v);
    
    //States;
    virtual void Hit() = 0; //hit by projectile
    virtual void Hurt() = 0; //hurt
    virtual void Collided(GameObject *other) = 0; //collided
    
    //Getters/Setters;
    virtual Vector2f getCenter() { return view.getOrigin(); };
    bool hasArmor(){ return armor > 0; };
    int addArmor(int value = 1){ armor+=value; return armor; };
    int removeArmor(int value = 1){ armor-=value; return armor; };
    int addLife(int value = 1){ hp+=value; return hp; };
    int removeLife(int value = 1){hp-=value; return hp; };
    bool isDead(){ return hp <= 0; };
    bool isInvulnerable(){ return invulnerabilityDuration > currentTime - invulnerabilityStartTime; };
    
    //Render.
    void CreateView();
    virtual void Update(float deltaTime) = 0;
    virtual void Draw();
    
    //Tructors.
    GameObject(Vector2f size, RenderWindow *window, BucketGrid *bucket);
    GameObject(Vector2f size, Vector2f position, RenderWindow *window, BucketGrid *bucket);
    GameObject(Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket);
    ~GameObject();

};
