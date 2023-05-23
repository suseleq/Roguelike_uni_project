#include "Game.h"

void Game::initWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1024, 900), "siema");
}

void Game::updateSfmlEvent()
{
	while (this->window->pollEvent(e))
	{
		if(this->e.type == sf::Event::Closed)
			this->window->close();
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

void Game::update()
{
	this->dt = this->dtClock.restart().asSeconds();
	this->updateSfmlEvent();
}

void Game::render()
{
	this->window->clear(sf::Color(213, 41, 76));

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}
