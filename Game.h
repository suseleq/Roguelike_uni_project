#pragma once
#include "Slime.h"
#include "Entity.h"
#include "CrystalBowl.h"
#include "Character.h"
#include "Bullet.h"
#include "Ghost.h"
#include "Skeleton.h"
#include "Menu.h"
#include <iostream>
#include <algorithm>

class Game
{
private:
	enum GameState 
	{
		mainMenu,
		pauseMenu,
		game,
		buff
	};

	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Menu> menu;

	GameState state;

	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<std::unique_ptr<Bullet>> bullets;
	std::unique_ptr<Character> character;

	sf::Event e;
	sf::Clock dtClock;
	float dt;
	sf::Vector2f mousePosition;


	//init functions
	void initWindow();
	void initGame();
	void startGame();


	void updateEntities();
	void updateBullets();
	void updateSfmlEvent();


public:
	Game();
	~Game();

	//update functions
	void update();

	void renderGame();
	void render();
	void run();
};

