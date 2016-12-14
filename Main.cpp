
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
void Level2();
void Exit();

sf::Font font;
sf::Texture backgroundImage;
sf::Sprite background;
sf::RenderWindow *window;

Ship *ship;

int margin = 10;
int score = 0;
bool isPlaying;
bool hasWon;
bool goMenu;

int WinMain()
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
	isPlaying = true;
	//Create rect;
	for (int i = 0; i < 10; i++)
	{
		//Do a dice roll, if it's 0, give armor.
		bool hasArmor = (rand() % 10) < 1;
		Asteroid *asteroid = new Asteroid(Vector2f(10, 10), rand() % 360, Vector2f(50, 50), window, &bucket);
		asteroid->view.setPosition(rand() % window->getSize().x, rand() % window->getSize().y);
		asteroid->armor = hasArmor;
		bucket.Push(asteroid);
	}

	Ship *ship = new Ship(Vector2f(100, 100), Vector2f(0, 0), Vector2f(20, 20), window, &bucket);
	//ship->hasBurstShot = true;
	//ship->hasTrishot = true;
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

	sf::Text title2;
	title2.setFont(font);
	title2.setString("None                       Armor: " + to_string(ship->armor));
	title2.setCharacterSize(21);
	title2.setFillColor(sf::Color::Yellow);
	title2.setOutlineColor(sf::Color::Black);
	title2.setOutlineThickness(2);
	title2.setPosition(title.getPosition().x - title2.getLocalBounds().width - margin * 10, window->getSize().y - title2.getLocalBounds().height - margin * 2);

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
	int activeAsteroids = 10;
	// Start the game loop
	while (window->isOpen() && isPlaying)
	{
		deltaTime = clock.restart().asSeconds();

		activeAsteroids = count_if(bucket.objects.begin(), bucket.objects.end(), [](GameObject *obj) { return obj->type == "asteroid"; });
		//std::cout << "ASTEROIDS: " << activeAsteroids << std::endl;
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

		std::string powerup = ship->hasBurstShot ? "Burst" : "None";
		powerup = ship->hasTrishot ? "Trishot" : powerup;

		std::string invul = ship->isInvulnerable() ? "Invulnerable    " : "";

		title2.setString(powerup + "      " + invul + " Armor: " + to_string(ship->armor));
		title.setString("Lives: " + to_string(ship->hp));
		scoreLabel.setString("Score: " + to_string(ship->score));

		window->draw(background);
		//Update bucket;
		bucket.Update(deltaTime);

		// Update the window
		window->draw(title);
		window->draw(title2);
		window->draw(scoreLabel);
		window->display();

		if (!ship->isActive)
		{
			isPlaying = false;
			hasWon = false;
		}

		if (activeAsteroids <= 0)
		{
			isPlaying = false;
			hasWon = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			isPlaying = false;
			goMenu = true;
			hasWon = false;
		}
	}
	score += ship->score;
	if (hasWon)
		Level2();
	else if (!hasWon && !goMenu)
		GameOver();
	else if (!hasWon && goMenu)
		Menu();
}
void Level2()
{
	BucketGrid bucket;

	int activeAsteroids = 20;

	//Create rect;
	for (int i = 0; i < activeAsteroids; i++)
	{
		//Do a dice roll, if it's 0, give armor.
		bool hasArmor = (rand() % 10) < 1;
		Asteroid *asteroid = new Asteroid(Vector2f(20, 20), rand() % 360, Vector2f(50, 50), window, &bucket);
		asteroid->view.setPosition(rand() % window->getSize().x, rand() % window->getSize().y);
		asteroid->armor = hasArmor;
		bucket.Push(asteroid);
	}

	Ship *ship = new Ship(Vector2f(100, 100), Vector2f(0, 0), Vector2f(20, 20), window, &bucket);
	//ship->hasBurstShot = true;
	//ship->hasTrishot = true;
	ship->score = score;
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

	sf::Text title2;
	title2.setFont(font);
	title2.setString("None                       Armor: " + to_string(ship->armor));
	title2.setCharacterSize(21);
	title2.setFillColor(sf::Color::Yellow);
	title2.setOutlineColor(sf::Color::Black);
	title2.setOutlineThickness(2);
	title2.setPosition(title.getPosition().x - title2.getLocalBounds().width - margin * 10, window->getSize().y - title2.getLocalBounds().height - margin * 2);

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
	while (window->isOpen() && !ship->isDead() && activeAsteroids > 0)
	{
		deltaTime = clock.restart().asSeconds();

		activeAsteroids = count_if(bucket.objects.begin(), bucket.objects.end(), [](GameObject *obj) { return obj->type == "asteroid"; });
		//std::cout << "ASTEROIDS: " << activeAsteroids << std::endl;
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
		std::string powerup = ship->hasBurstShot ? "Burst" : "None";
		powerup = ship->hasTrishot ? "Trishot" : powerup;
		std::string invul = ship->isInvulnerable() ? "Invulnerable    " : "";


		title2.setString(powerup + "      " + invul + " Armor: " + to_string(ship->armor));
		title.setString("Lives: " + to_string(ship->hp));
		scoreLabel.setString("Score: " + to_string(ship->score));

		window->draw(background);
		//Update bucket;
		bucket.Update(deltaTime);

		// Update the window
		window->draw(title);
		window->draw(title2);
		window->draw(scoreLabel);
		window->display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			isPlaying = false;
		}
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			isPlaying = false;
			goMenu = true;
			hasWon = false;
		}
	}

	if (hasWon)
		Menu();
	else if (!hasWon && !goMenu)
		GameOver();
	else if (!hasWon && goMenu)
		Menu();
}
