#include "Game.h"

void Game::initWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1024, 900), "siema");
}

void Game::initGame()
{
	std::unique_ptr<Entity> background(new Entity("background"));
	this->entities.emplace_back(std::move(background));

	
	std::unique_ptr<Entity> bowl(new CrystalBowl());
	bowl->setPosition(this->window->getSize().x / 2 - bowl->getGlobalBounds().width / 2,
		this->window->getSize().y / 2 - bowl->getGlobalBounds().height / 2);
	this->entities.emplace_back(std::move(bowl));
	

	std::unique_ptr<Entity> character(new Character());
	this->entities.emplace_back(std::move(character));

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
	this->initGame();
}

Game::~Game()
{
}

void Game::update()
{
	this->dt = this->dtClock.restart().asSeconds();

	for (auto& i : this->entities)
	{
		i->update(this->dt);
	}

	this->updateSfmlEvent();
}

void Game::render()
{
	this->window->clear(sf::Color(213, 41, 76));
	for (auto& i : this->entities)
	{
		i->render(*this->window);
	}
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
