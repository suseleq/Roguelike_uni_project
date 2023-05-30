#pragma once
#include "Slime.h"
#include "Entity.h"
#include "CrystalBowl.h"
#include "Character.h"
#include "Bullet.h"
#include <iostream>
#include <algorithm>

class Game
{
private:
	std::unique_ptr<sf::RenderWindow> window;

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
	
	void updateEntities();
	void updateBullets();
	void updateSfmlEvent();


public:
	Game();
	~Game();

	//update functions
	void update();


	void render();
	void run();
};

