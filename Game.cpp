#include "Game.h"

void Game::initWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1024, 900), "siema");
}

void Game::updateSfmlEvent()
{
	while (this->window.get()->pollEvent(e))
	{
		if(this->e.type == sf::Event::Closed)
			this->window.get()->close();
	}
}

Game::Game()
{
	this->dt = 0.f;
	this->initWindow();
}

Game::~Game()
{
}

void Game::uptade()
{
	this->dt = this->dtClock.restart().asSeconds();
	this->updateSfmlEvent();
}

void Game::render()
{
	this->window.get()->clear(sf::Color(213, 41, 76));

	this->window.get()->display();
}

void Game::run()
{
	while (this->window.get()->isOpen())
	{
		this->uptade();
		this->render();
	}
}
