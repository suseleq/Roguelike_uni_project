#include "Game.h"

void Game::initWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1024, 900), "siema");
	this->window->setFramerateLimit(60);
}

void Game::initGame()
{
	std::unique_ptr<Entity> background(new Entity("background"));
	this->entities.emplace_back(std::move(background));

	
	std::unique_ptr<Entity> bowl(new CrystalBowl());
	bowl->setPosition(this->window->getSize().x / 2 - bowl->getGlobalBounds().width / 2,
		this->window->getSize().y / 2 - bowl->getGlobalBounds().height / 2);
	this->entities.emplace_back(std::move(bowl));
	

	this->character = std::make_unique<Character>();
	this->character->setPosition(this->window->getSize().x / 2,
		this->window->getSize().y / 2 );

}

void Game::updateEntities()
{
	this->character->update(this->dt);
	for (auto& i : this->entities)
	{
		i->update(this->dt);
		i->attack(mousePosition, this->bullets);
		this->character->circleIntersection(i->getCircleBounds());
	}
	this->character->attack(mousePosition, this->bullets);
}

void Game::updateBullets()
{
	for (auto it = this->bullets.begin(); it != this->bullets.end();)
	{
		it->get()->uptade(dt);
		if (!it->get()->getGlobalBounds().intersects(sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y)))
		{
			it = this->bullets.erase(it);
		}
		else
		{
			++it;
		}
	}


}

void Game::updateSfmlEvent()
{
	while (this->window->pollEvent(e))
	{
		if(this->e.type == sf::Event::Closed)
			this->window->close();
	}
}

sf::Vector2f Game::normalizeVector(sf::Vector2i& v)
{
	float length = sqrt(pow(v.x, 2) + pow(v.y, 2));
	return sf::Vector2f(v.x / length, v.y / length);
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
	this->mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->dt = this->dtClock.restart().asSeconds();

	this->updateBullets();
	this->updateEntities();

	this->updateSfmlEvent();
}

void Game::render()
{
	this->window->clear(sf::Color(213, 41, 76));
	
	for (auto& i : this->entities)
	{
		i->render(*this->window);
	}
	this->character->render(*this->window);
	for (auto& i : this->bullets)
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
