//
//  Ship.cpp
//  Asteroids
//
//  Created by Rogelio Espinoza on 12/13/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#include "Ship.h"
#include "BucketGrid.h"

Ship::Ship(Vector2f speed, float angle, Vector2f size, RenderWindow *window, BucketGrid *bucket) : ControlledObject(speed, angle, size, window, bucket)
{
    Init();
}
Ship::Ship(Vector2f speed, Vector2f direction, Vector2f size, RenderWindow *window, BucketGrid *bucket) : ControlledObject(speed, direction, size, window, bucket)
{
    Init();
}
Ship::Ship(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, RenderWindow *window, BucketGrid *bucket) : ControlledObject(speed, direction, size, position, window, bucket)
{
    Init();
}
Ship::Ship(Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket) : ControlledObject(speed, direction, size, position, texture, window, bucket)
{
    Init();
}
Ship::Ship(Keyboard::Key up, Keyboard::Key down, Keyboard::Key left, Keyboard::Key right, Keyboard::Key primary, Keyboard::Key secondary, Vector2f speed, Vector2f direction, Vector2f size, Vector2f position, Texture texture, RenderWindow *window, BucketGrid *bucket) : ControlledObject(up, down, left, right, primary, secondary, speed, direction, size, position, texture, window, bucket)
{
    Init();
}

Ship::~Ship()
{
    
}

void Ship::Init()
{
	this->type = "ship";
    texture.loadFromFile("spaceship.png");
    //view.setTextureRect(IntRect(0, 0, 10, 10));
    view.setTexture(&texture);
    
    buffer.loadFromFile("Assets/sounds/engine.ogg");
    sound.setBuffer(buffer);
}

void Ship::Up()
{
    //std::cout << "U" << std::endl;
    acceleration = speed;
    if(sound.getStatus() != Sound::Status::Playing)
        sound.play();
}
void Ship::Down()
{
    //std::cout << "D" << std::endl;
}
void Ship::Left()
{
    //std::cout << "L" << std::endl;
    view.rotate(rotationSpeed * deltaTime * -1);
}
void Ship::Right()
{
    //std::cout << "R" << std::endl;
    view.rotate(rotationSpeed * deltaTime );
}
void Ship::Primary()
{
    //std::cout << "1" << std::endl;
    if(!isShooting && shotCooldown <= (currentTime - lastShot))
        Shoot();
    //else
        //std::cout << "NOT HOST" << std::endl;
}
void Ship::Secondary()
{
    //std::cout << "2" << std::endl;
    
}

void Ship::Collided(GameObject *other)
{
    if(other->type == "asteroid")
    {
        this->Hit();
    }
	else if (other->type == "powerup")
	{
		std::cout << "POWERUP! " << std::endl;
		PowerUp *powerup = dynamic_cast<PowerUp*>(other);
		GetPowerUp(powerup->power);
	}
}
void Ship::GetPowerUp(PowerUp::PowerType power)
{
	switch (power)
	{
		case PowerUp::PowerType::burst:
			hasBurstShot = true;
			hasTrishot = false;
			break;
		case PowerUp::PowerType::shield:
			armor = 3;
			break;
		case PowerUp::PowerType::trishot:
			hasTrishot = true;
			hasBurstShot = false;
			break;
		case PowerUp::PowerType::superstar:
			StartInvulnerability();
			break;
		default:
			break;
	}
}

Vector2f Ship::Move()
{
    if(acceleration.x > 0) acceleration.x -= friction * deltaTime; else acceleration.x = 0;
    if(acceleration.y > 0) acceleration.y -= friction * deltaTime; else acceleration.y = 0;
    
    float rotationRadians = view.getRotation() * PI / 180;
    
    direction.x = cosf(rotationRadians);
    direction.y = sinf(rotationRadians);
    
    view.move(acceleration.x * direction.x * deltaTime, acceleration.y * direction.y * deltaTime);

	return view.getPosition();
}

void Ship::ShootBomb()
{
    
}
void Ship::ResetAmmo()
{
	if (!hasBurstShot && !hasTrishot)
	{
		bulletsPerShot = 1;
		rateOfFire = 0;
		shotCooldown = 0.25f;
	}
}
void Ship::SetBurst()
{
    if(hasBurstShot)
    {
        bulletsPerShot = 3;
		rateOfFire = 0.1f;
		shotCooldown = 0.5f;
    }
}
void Ship::SetTrishot()
{
	if (hasTrishot)
	{
		bulletsPerShot = 3;
		rateOfFire = 0;
		shotCooldown = 0.35f;
	}
}
void Ship::Shoot()
{
	ResetAmmo();
    SetBurst();
	SetTrishot();
    isShooting = true;
    bulletsShot = 0;
    
    for(int i = 0; i < bulletsPerShot; i++)
    {
    }
    
    lastShot = currentTime;
}

void Ship::Shooting()
{
    if(bulletsShot < bulletsPerShot)
    {
        if(rateOfFire <= (currentTime - lastBullet))
        {
			float bulletAngle = this->view.getRotation();

			if (hasTrishot)
			{
				//Change the angle so it bursts in a fork way.
				bulletAngle = bulletAngle - 25 + 25 * bulletsShot;
			}

            Bullet *bullet = new Bullet(Vector2f(200,200), bulletAngle, Vector2f(5,5), window, bucket, this);
            bullet->view.setPosition(this->view.getPosition());
            //bullets.push_back(bullet);
            bulletsShot++;
            lastBullet = currentTime;
            
            bucket->Push(bullet);
        }
    }
    else
    {
        isShooting = false;
        lastShot = currentTime;
        bulletsShot = 0;
    }
}
void Ship::Reset()
{
    this->view.setPosition(window->getSize().x * 0.5f, window->getSize().y * 0.5f);
}
void Ship::Update(float deltaTime)
{
    //std::cout << "UPDATE MO" << std::endl;
    this->deltaTime = deltaTime;
    currentTime += deltaTime;
    
    //Update bullets;
    /*
    for(Bullet *b : bullets)
    {
        b->Update(deltaTime);
    }
     */
    
    Control();
    Move();
    if(isShooting) Shooting();
    Wrap();
    Draw();
    
}
