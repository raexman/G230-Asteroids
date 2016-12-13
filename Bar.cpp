#include "Bar.h"



Bar::Bar(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture):MovableGameObject(size, position, window, texture)
{
	Init();
}

void Bar::Init()
{
	speed.x = 100;
	speed.y = 100;
	isMoving = true;
	view.setOutlineColor(sf::Color::Black);
	view.setOutlineThickness(2);
	view.setOrigin(view.getSize().x * 0.5f, view.getSize().y*0.5f);
	SetWalls(false, false, false, false);
	isWrapping = true;
}

Bar::~Bar()
{
}

void Bar::Update(float deltaTime)
{
	this->deltaTime = deltaTime;

	//if (!isActive) return;

	Control();
	Move();
	Draw();
	if (bullet)bullet->Update(deltaTime);
}

void Bar::Control()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		std::cout << "ROTATION: " << view.getRotation() << std::endl;
		view.rotate(90 * deltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		std::cout << "ROTATION: " << view.getRotation() << std::endl;
		view.rotate(-90 * deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		acceleration = speed;
		float radians = view.getRotation() * PI / 180;
		direction.x = cosf(radians);
		direction.y = sinf(radians);
		std::cout << "DIRECTION: " << cosf(radians) << " | " << sinf(radians) << " ANGLE: " << view.getRotation() << " RADIANS: " << radians << " PI: " << PI << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		acceleration = speed;
		float radians = view.getRotation() * PI / 180;
		direction.x = cosf(radians) * -1;
		direction.y = sinf(radians) * -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		std::cout << "SHOOT!" << std::endl;
		//SHOOT FUCKING BALL
		bullet = new Ball(sf::Vector2f(500, 500), 1, sf::Vector2f(10, 10), view.getPosition(), window, texture);
		bullet->SetDirection(direction.x, direction.y);
		bullet->StartMoving();
	}
}

void Bar::Collided(sf::Vector2f point)
{
	buffer.loadFromFile("bumper.wav");
	sound.setBuffer(buffer);
	sound.play();
}

void Bar::Move() {

	if (topWall)
	{
		if (view.getPosition().y <= 0)
		{
			SetDirection(-2, 1);
			std::string soundFx = "bounce.wav";
			buffer.loadFromFile(soundFx);
			sound.setBuffer(buffer);
			sound.play();
		}
	}
	if (rightWall)
	{
		if (view.getPosition().x + view.getSize().x >= window->getSize().x)
		{
			SetDirection(-1, -2);
			std::string soundFx = "bounce.wav";
			buffer.loadFromFile(soundFx);
			sound.setBuffer(buffer);
			sound.play();
		}
	}
	if (bottomWall)
	{
		if (view.getPosition().y + view.getSize().y >= window->getSize().y)
		{
			SetDirection(-2, -1);
			std::string soundFx = "bounce.wav";
			buffer.loadFromFile(soundFx);
			sound.setBuffer(buffer);
			sound.play();
		}
	}
	if (leftWall)
	{
		if (view.getPosition().x <= 0)
		{
			SetDirection(1, -2);
			std::string soundFx = "bounce.wav";
			buffer.loadFromFile(soundFx);
			sound.setBuffer(buffer);
			sound.play();
		}
	}

	if (isWrapping)
	{

		if (view.getPosition().x + view.getSize().x < 0)
		{
			view.setPosition(view.getSize().x, view.getPosition().y);
		}
		else if (view.getPosition().x > window->getSize().x)
		{
			view.setPosition(0, view.getPosition().y);
		}

		if (view.getPosition().y + view.getSize().y < 0)
		{
			view.setPosition(view.getPosition().x, view.getSize().y);
		}
		else if (view.getPosition().y > window->getSize().y)
		{
			view.setPosition(view.getPosition().x, 0);
		}
	}

	//Automatically move object.
	if (acceleration.x > 0) acceleration.x -= 500 * deltaTime; else acceleration.x = 0;
	if (acceleration.y > 0) acceleration.y -= 500 * deltaTime; else acceleration.y = 0;

	sf::Vector2f distance(acceleration.x * direction.x * deltaTime, acceleration.y * direction.y * deltaTime);
	this->view.move(distance);

}