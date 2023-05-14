#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
class Game
{
private:
	std::unique_ptr<sf::RenderWindow> window;


	sf::Event e;
	sf::Clock dtClock;
	float dt;


	void initWindow();
	void updateSfmlEvent();


public:
	Game();
	~Game();


	void uptade();
	void render();
	void run();
};

