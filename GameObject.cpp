//
//  GameObject.cpp
//  Asteroids
//
//  Created by Rogelio Espinoza on 12/13/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#include "GameObject.h"
#include "BucketGrid.h"

GameObject::GameObject(Vector2f size, RenderWindow *window, BucketGrid *bucket)
{
    this->size = size;
    this->window = window;
    this->position = Vector2f(0,0);
    this->bucket = bucket;
    
    CreateView();
}
GameObject::GameObject(Vector2f size, Vector2f position, RenderWindow *window, BucketGrid *bucket)
{
    this->size = size;
    this->position = position;
    this->window = window;
    this->bucket = bucket;

    CreateView();
}

GameObject::GameObject(Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket)
{
    this->size = size;
    this->position = position;
    this->texture = texture;
    this->window = window;
    this->bucket = bucket;

    CreateView();
}

GameObject::~GameObject()
{
    
}

void GameObject::Update(float deltaTime)
{
    std::cout << "UPDATE GO" << std::endl;
    this->deltaTime = deltaTime;
    Draw();
}

void GameObject::Draw()
{
    this->window->draw(view);
}

void GameObject::CreateView()
{
    view = CircleShape(size.x);
    view.setPosition(this->position);
    view.setOrigin(view.getRadius(), view.getRadius());
}

bool GameObject::CheckCollisionWith(GameObject *other)
{

    float d = length(this->view.getPosition() - other->view.getPosition());
    float sum = this->view.getRadius() + other->view.getRadius();
    bool hasCollided = d < sum;
    
    if(hasCollided){
        Collided(other);
        other->Collided(this);
    }
    
    return hasCollided;
}
/*
bool GameObject::CheckCollisionWith(GameObject *other)
{
    Vector2f thisMin = Vector2f(std::min(this->view.getPosition().x, this->view.getPosition().x + this->view.getSize().x),
                                std::min(this->view.getPosition().y, this->view.getPosition().y + this->view.getSize().y));
    Vector2f thisMax = Vector2f(std::max(this->view.getPosition().x, this->view.getPosition().x + this->view.getSize().x),
                                std::max(this->view.getPosition().y, this->view.getPosition().y + this->view.getSize().y));
    Vector2f otherMin = Vector2f(std::min(other->view.getPosition().x, other->view.getPosition().x + other->view.getSize().x),
                                 std::min(other->view.getPosition().y, other->view.getPosition().y + other->view.getSize().y));
    Vector2f otherMax = Vector2f(std::max(other->view.getPosition().x, other->view.getPosition().x + other->view.getSize().x),
                                 std::max(other->view.getPosition().y, other->view.getPosition().y + other->view.getSize().y));
    
    bool hasCollided = (thisMin.x <= otherMax.x && thisMax.x >= otherMin.x) && (thisMin.y <= otherMax.y && thisMax.y >= otherMin.y);
    
    if(hasCollided){
        Collided(other);
        other->Collided(this);
    }
    
    return hasCollided;
}
*/

float GameObject::length(Vector2f v)
{
    return sqrtf(v.x*v.x + v.y*v.y);
}

void GameObject::StartInvulnerability()
{
	invulnerabilityStartTime = currentTime;
	
}