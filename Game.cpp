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
	this->entities.clear();
	this->bullets.clear();
	this->randomAngle = std::uniform_real_distribution<float>(-3.14f, 3.14f);


	std::unique_ptr<Entity> bowl(new MagicBowl());
	bowl->setPosition(this->window->getSize().x / 2 - bowl->getGlobalBounds().width / 2,
		this->window->getSize().y / 2 - bowl->getGlobalBounds().height / 2);
	this->entities.emplace_back(std::move(bowl));

	this->character = std::make_unique<Character>();
	this->character->setPosition(this->window->getSize().x / 2,
		this->window->getSize().y / 2);
	this->character->setScreenBounds(sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y));

	sf::Vector2f pos = sf::Vector2f(100, 100);

	this->gui = std::make_unique<GameInformation>(this->character->getHealth(),
		this->character->getPoints(),
		this->character->getLevel());

	this->spawnSlime();
	this->spawnSlime();

}

sf::Vector2f Game::randomPosition()
{
	return sf::Vector2f(this->window->getSize().x / 2 + (this->window->getSize().x / 2 - 30) * cos(this->randomAngle(rd)),
		this->window->getSize().y / 2 + (this->window->getSize().y / 2 - 30) * sin(this->randomAngle(rd)));
}

void Game::spawnSlime()
{
	std::unique_ptr<Entity> slime(new Slime);
	slime->setPosition(this->randomPosition());
	this->entities.emplace_back(std::move(slime));
}

void Game::spawnGhost(const std::string& type)
{
	std::unique_ptr<Entity> ghost(new Ghost(type));
	ghost->setPosition(this->randomPosition());
	this->entities.emplace_back(std::move(ghost));
}

void Game::spawnSkeleton()
{
	std::unique_ptr<Entity> skeleton(new Skeleton(this->window->getSize().x / 2, this->window->getSize().y / 2));
	this->entities.emplace_back(std::move(skeleton));
}

void Game::updateCharacter()
{
	if (this->character->newLevel())
	{
		this->character->levelUp();
	}
	
	this->character->attack(mousePosition, this->bullets);
	if (this->character->getHealth() <= 0)
	{
		this->state = mainMenu;
		this->gui = std::make_unique<Menu>(true);
	}
	this->character->update(this->dt);
}



void Game::updateEntities()
{
	for (auto entity = this->entities.begin(); entity != this->entities.end();)
	{
		MagicBowl* bowl = dynamic_cast<MagicBowl*>(entity->get());
		Experience* exp = dynamic_cast<Experience*>(entity->get());
		
		//Update magicBowl
		if (bowl != nullptr)
		{
			bowl->update(this->dt);
			this->character->circleIntersection(bowl->getCircleBounds());
			++entity;
		}
		//Update experience
		else if(exp != nullptr)
		{
			exp->update(this->dt);
			if (exp->getHitboxBounds().intersects(this->character->getHitboxBounds()))
			{
				entity = this->entities.erase(entity);
				this->character->addExperience();
			}
			else
				++entity;
		}
		//Update enemies
		else
		{
			//Update life of enemy
			for (auto bullet = this->bullets.begin(); bullet != this->bullets.end();)
			{
				//Cheking if bullet hit			
				if (bullet->get()->getHitboxBounds().intersects(entity->get()->getHitboxBounds()) && !bullet->get()->getEnemyBullet())
				{
					//enemy get damage and delete bullet
					entity->get()->setHealthMinus(bullet->get()->getDamage());
					bullet = this->bullets.erase(bullet);
					
				}
				else
					bullet++;
			}
			//Checking if enemy is alive
			if (entity->get()->getHealth() <= 0)
			{
				//Getting points
				this->character->addPoints(entity->get()->getPoints());
				//Spawning experience from enemy
				std::unique_ptr<Entity> exp(new Experience());
				exp->setPosition(entity->get()->getPosition());
				//Deleting enemy and emplacing exp to vector
				entity = this->entities.erase(entity);
				entity = this->entities.emplace(entity, std::move(exp));
			}
			else
			{
				//Updating enemy
				entity->get()->update(sf::Vector2f(this->character->getPosition().x + this->character->getGlobalBounds().width / 2,
					this->character->getPosition().y + this->character->getGlobalBounds().height / 2), this->dt);
				this->character->circleIntersection(entity->get()->getCircleBounds());
				if (this->character->getGlobalBounds().intersects(entity->get()->getHitboxBounds()))
				{
					this->character->setHealthMinus(entity->get()->getDamage());
				}
				++entity;
			}

		}
	}
}


void Game::updateBullets()
{
	for (auto it = this->bullets.begin(); it != this->bullets.end();)
	{
		it->get()->update(dt);
		if (!it->get()->getGlobalBounds().intersects(sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y)))
		{
			it = this->bullets.erase(it);
		}
		else if (it->get()->getHitboxBounds().intersects(this->character->getHitboxBounds()) && it->get()->getEnemyBullet())
		{
			this->character->setHealthMinus(it->get()->getDamage());
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
		if (this->e.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::updateGui()
{
	//Pause Game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->state == game)
	{
		this->state = pauseMenu;
		this->gui = std::make_unique<Menu>(false);
	}
	Menu* menu = dynamic_cast<Menu*>(this->gui.get());
	GameInformation* info = dynamic_cast<GameInformation*>(this->gui.get());
	Buffs* buff = dynamic_cast<Buffs*>(this->gui.get());
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
					this->gui = std::make_unique<GameInformation>(this->character->getHealth(),
						this->character->getPoints(),
						this->character->getLevel());
					break;
				case 1:
					this->state = game;
					this->startGame();
					break;
				case 2:
					this->window->close();
				}

			}
			else if (this->state == mainMenu)
			{
				switch (menu->getOption())
				{
				case 0:
					this->state = game;
					this->startGame();
					break;
				case 1:
					this->window->close();
				}
			}
		}
	}
	else if (info != nullptr) 
	{
	info->update(this->character->getHealth(),
		this->character->getPoints(),
		this->character->getLevel());	
	}
	else if (buff != nullptr)
	{
		buff->update(this->dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->state == buffState)
		{
			switch (buff->getOption())
			{
			case 0:
				this->character->velocityBuff();
				break;
			case 1:
				this->character->setHealthPlus(1);
				break; 
			case 2:
				this->character->damageBuff();
				break; 
			case 3:
				this->character->attackSpeedBuff();
				break; 
			case 4:
				this->character->bulletBuff();
				break;
			case 5:
				for (auto& i : this->entities)
					i->expandRadiusCircle();
				break;
			}
		}
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
		this->updateCharacter();
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
