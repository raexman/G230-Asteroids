#pragma once
#include "GameObject.h"
class PowerUp :
	public GameObject
{
public:
	static const enum PowerType { shield, burst, trishot, superstar };
	PowerType power;
	void Hurt() { if (armor > 0) { armor--; } else { hp--; } }; //hurt
	void Hit() { Hurt(); if (hp <= 0) isActive = false; }; //hit by projectile
	void Collided(GameObject *other); //collided
	//Getters/Setters;
	void Update(float deltaTime);
	void Draw();
	Vector2f getCenter() { return view.getPosition(); };
	PowerUp(int type, Vector2f size, RenderWindow *window, BucketGrid *bucket);
	~PowerUp();
	void Init();
};

