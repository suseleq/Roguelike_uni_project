#pragma once
#include "Slime.h"
#include "Entity.h"
#include "MagicBowl.h"
#include "Character.h"
#include "Bullet.h"
#include "Ghost.h"
#include "Skeleton.h"
#include "Menu.h"
#include "GUI.h"
#include "Buffs.h"
#include "GameInformation.h"
#include "Experience.h"
#include <iostream>
#include <algorithm>


class Game
{
private:
	//Variables
	enum GameState 
	{
		mainMenu,
		pauseMenu,
		game,
		buffState
	};

	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<GUI> gui;

	GameState state;

	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<std::unique_ptr<Bullet>> bullets;
	std::unique_ptr<Character> character;

	sf::Event e;
	sf::Clock dtClock;
	float dt;
	sf::Vector2f mousePosition;
	std::random_device rd;
	std::uniform_real_distribution <float> randomAngle;

	std::map <std::string, float> spawningEnmyTimer;

	//init functions
	void initWindow();
	void initGame();
	void startGame();
	void initBuffs();

	//Spawn enemy functions
	sf::Vector2f randomPosition();
	void spawnSlime();
	void spawnGhost(const std::string& type);
	void spawnSkeleton();

	//update functions
	void updateSpawningEnemies();
	void updateCharacter();
	void updateEntities();
	void updateBullets();
	void updateSfmlEvent();
	void updateGui();
	void update();

	void renderGame();
	void render();

public:
	Game();
	~Game();

	void run();
};

