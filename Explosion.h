#pragma once
#include "GameObject.h"
class Explosion :
	public GameObject
{
public:
	float duration;
	float explosionStart;

	void Hurt() { if (armor > 0) { armor--; } else { hp--; } }; //hurt
	void Hit() { Hurt(); if (hp <= 0) isActive = false; }; //hit by projectile
	void Collided(GameObject *other) {}; //collided
	
	//Getters/Setters;
	Vector2f getCenter() { return view.getPosition(); };

	void Update(float deltaTime);
	void Draw();
	Explosion(int duration, Vector2f size, RenderWindow *window, BucketGrid *bucket);
	~Explosion();
};

