#pragma once
#include "Entity.h"
class Game
{
private:
	std::unique_ptr<sf::RenderWindow> window;


	sf::Event e;
	sf::Clock dtClock;
	float dt;

	//init functions
	void initWindow();
	
	
	void updateSfmlEvent();


public:
	Game();
	~Game();

	//update functions
	void update();


	void render();
	void run();
};

