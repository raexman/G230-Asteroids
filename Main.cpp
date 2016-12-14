
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.h
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "BucketGrid.h"
#include "Asteroid.h"
#include "Ship.h"

void Menu();
void GameOver();
void Level1();
void Exit();

sf::Font font;
sf::Texture backgroundImage;
sf::Sprite background;
sf::RenderWindow *window;

Ship *ship;

int margin = 10;
int score = 0;

int main()
{
    
	// Create the main window
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Orion's Belt");
	
	font.loadFromFile("AmericanCaptain.ttf");


    // Load a sprite to display
	backgroundImage.loadFromFile("background.jpg");
	background = Sprite(backgroundImage);

	Menu();
	
    return 0;
}


void Menu()
{
	bool optionChosen = false;
	int mode = 0;

	while (window->isOpen() && !optionChosen)
	{
		sf::Text title;
		title.setFont(font);
		title.setString("ORION'S BELT");
		title.setCharacterSize(125);
		title.setFillColor(sf::Color::White);
		title.setPosition((window->getSize().x - title.getLocalBounds().width) * 0.5, 100);

		sf::Text menu;
		menu.setFont(font);
		menu.setString("[Press SPACE to start]");
		menu.setCharacterSize(48);
		menu.setFillColor(sf::Color::White);
		menu.setPosition((window->getSize().x - menu.getLocalBounds().width) * 0.5, title.getPosition().y + title.getGlobalBounds().height + 50);

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				return;
			}
		}

		window->clear();
		window->draw(background);
		window->draw(menu);
		window->draw(title);
		window->display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			mode = 1;
			optionChosen = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		{
			mode = 2;
			optionChosen = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
		{
			mode = 3;
			optionChosen = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
		{
			mode = 4;
			optionChosen = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			mode = 0;
			optionChosen = true;
		}
	}
	switch (mode)
	{
		case 0: Exit();
		case 1: Level1(); break;
		case 2: GameOver(); break;
		default:break;
	}
}
void Exit()
{

}
void Level1()
{
	BucketGrid bucket;

	//Create rect;
	for (int i = 0; i < 3; i++)
	{
		Asteroid *asteroid = new Asteroid(Vector2f(10, 10), rand() % 360, Vector2f(50, 50), window, &bucket);
		asteroid->view.setPosition(rand() % window->getSize().x, rand() % window->getSize().y);
		bucket.Push(asteroid);
	}

	Ship *ship = new Ship(Vector2f(100, 100), Vector2f(0, 0), Vector2f(20, 20), window, &bucket);
	//ship->hasBurstShot = true;
	ship->view.setPosition(window->getSize().x * 0.5f, window->getSize().y * 0.5f);
	bucket.Push(ship);

	sf::Text title;
	title.setFont(font);
	title.setString("Lives: " + to_string(ship->hp));
	title.setCharacterSize(21);
	title.setFillColor(sf::Color::Yellow);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(2);
	title.setPosition(window->getSize().x - title.getLocalBounds().width - margin * 2, window->getSize().y - title.getLocalBounds().height - margin * 2);

	sf::Text scoreLabel;
	scoreLabel.setFont(font);
	scoreLabel.setString("Score: " + to_string(ship->score));
	scoreLabel.setCharacterSize(21);
	scoreLabel.setFillColor(sf::Color::Yellow);
	scoreLabel.setOutlineColor(sf::Color::Black);
	scoreLabel.setOutlineThickness(2);
	scoreLabel.setPosition(margin * 2, window->getSize().y - scoreLabel.getLocalBounds().height - margin * 2);


	sf::Clock clock;
	float deltaTime;

	// Start the game loop
	while (window->isOpen() && !ship->isDead())
	{
		deltaTime = clock.restart().asSeconds();
		// Process events
		sf::Event event;
		while (window->pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed) {
				window->close();
			}

			// Escape pressed: exit
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window->close();
			}
		}

		// Clear screen
		window->clear();

		title.setString("Lives: " + to_string(ship->hp));
		scoreLabel.setString("Score: " + to_string(ship->score));

		window->draw(background);
		//Update bucket;
		bucket.Update(deltaTime);

		// Update the window
		window->draw(title);
		window->draw(scoreLabel);
		window->display();
	}

	GameOver();
}

void GameOver()
{
	bool optionChosen = false;
	while (window->isOpen() && !optionChosen)
	{
		sf::Text menu;
		menu.setFont(font);
		menu.setString("GAME OVER!");
		menu.setCharacterSize(96);
		menu.setFillColor(sf::Color::White);
		menu.setPosition((window->getSize().x - menu.getLocalBounds().width) * 0.5, (window->getSize().y - menu.getLocalBounds().height) * 0.5);

		sf::Text subtitle;
		subtitle.setFont(font);
		subtitle.setString("Press [SPACEBAR] to go to Menu");
		subtitle.setCharacterSize(48);
		subtitle.setFillColor(sf::Color::White);
		subtitle.setPosition((window->getSize().x - subtitle.getLocalBounds().width) * 0.5, menu.getPosition().y + menu.getLocalBounds().height + 50);

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				return;
			}
		}

		window->clear();
		window->draw(background);
		window->draw(menu);
		window->draw(subtitle);
		window->display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			optionChosen = true;
		}
	}

	Menu();
}
