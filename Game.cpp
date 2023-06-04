#include "Game.h"

void Game::initWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1024, 900), "Projekt");
	this->window->setFramerateLimit(60);
}

void Game::initGame()
{
	this->gui = std::make_unique<Menu>(true);
	this->state = mainMenu;
}

void Game::startGame()
{
	std::unique_ptr<Entity> bowl(new CrystalBowl());
	bowl->setPosition(this->window->getSize().x / 2 - bowl->getGlobalBounds().width / 2,
		this->window->getSize().y / 2 - bowl->getGlobalBounds().height / 2);
	this->entities.emplace_back(std::move(bowl));
	
	this->character = std::make_unique<Character>();
	this->character->setPosition(this->window->getSize().x / 2,
		this->window->getSize().y / 2);
	this->character->setScreenBounds(sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y));

	std::unique_ptr<Entity> slime(new Slime());
	this->entities.emplace_back(std::move(slime));



	this->gui = std::make_unique<GUI>(this->character->getHealth(),
		this->character->getPoints(),
		this->character->getLevel());
}

void Game::updateEntities()
{
	this->character->update(this->dt);
	for (auto entity = this->entities.begin(); entity != this->entities.end();)
	{
		CrystalBowl* bowl = dynamic_cast<CrystalBowl*> (entity->get());
		if (bowl != nullptr)
		{
			bowl->update(this->dt);
			++entity;
		}
		else
		{
			bool isDead = false;
			for (auto bullet = this->bullets.begin(); bullet != this->bullets.end();)
			{
				bullet->get()->uptade(dt);
				if (bullet->get()->getHitboxBounds().intersects(entity->get()->getHitboxBounds()) && !bullet->get()->getEnemyBullet())
				{
					bullet = this->bullets.erase(bullet);
					entity->get()->setHealthMinus(this->character->getDamage());
					if (entity->get()->getHealth() <= 0)
					{
						isDead = true;
					}
				}
				else
				{
					++bullet;
				}
			}
			if (isDead)
			{
				entity = this->entities.erase(entity);
			}
			else
			{
				entity->get()->update(sf::Vector2f(this->character->getPosition().x + this->character->getGlobalBounds().width / 2,
					this->character->getPosition().y + this->character->getGlobalBounds().height / 2), this->dt);
				entity->get()->attack(mousePosition, this->bullets);
				this->character->circleIntersection(entity->get()->getCircleBounds());
				++entity;
			}
		}
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

void Game::updateGui()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && (this->state == game || this->state == buff))
	{
		this->state = pauseMenu;
		this->gui = std::make_unique<Menu>(false);
	}

	Menu* menu = dynamic_cast<Menu*>(this->gui.get());
	if (menu != nullptr)
	{
		menu->update(this->dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (this->state == pauseMenu)
			{
				switch (menu->getOption())
				{
				case 0:
					this->state = game;
					this->gui = std::make_unique<GUI>(this->character->getHealth(), 
						this->character->getPoints(), 
						this->character->getLevel());
					break;
				case 1:
					break;
				case 2:
					this->window->close();
				default:
					break;
				}
			}
			if (this->state == mainMenu)
			{
				switch (menu->getOption())
				{
				case 0:
					this->state = game;
					this->startGame();
					break;
				case 1:
					this->window->close();
				default:
					break;
				}
			}
		}
	}
	else 
	{
		this->gui->update(this->character->getHealth(),
			this->character->getPoints(),
			this->character->getLevel());
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
	this->updateSfmlEvent();
	
	if (this->state == game)
	{
		this->mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
		this->updateBullets();
		this->updateEntities();
	}
	this->updateGui();
}

void Game::renderGame()
{
	this->character->render(*this->window);
	for (auto& i : this->entities)
	{
		i->render(*this->window);
	}
	for (auto& i : this->bullets)
	{
		i->render(*this->window);
	}
}

void Game::render()
{
	this->window->clear(sf::Color(18, 14, 28));
	if (this->state == game)
	{
		this->renderGame();
	}
	this->gui->render(*this->window);
	
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
