#pragma once
#include "Entity.h"
#include "CrystalBowl.h"


class Game
{
private:
	std::unique_ptr<sf::RenderWindow> window;

	std::vector<std::unique_ptr<Entity>> entities;


	sf::Event e;
	sf::Clock dtClock;
	float dt;

	//init functions
	void initWindow();
	void initGame();
	
	void updateSfmlEvent();


public:
	Game();
	~Game();

	//update functions
	void update();


	void render();
	void run();
};

