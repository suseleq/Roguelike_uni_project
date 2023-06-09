#include "Game.h"

void Game::initWindow()
{
	//creating window
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1024, 900), "Projekt");
	this->window->setFramerateLimit(60);
}

void Game::initGame()
{
	//Initialize main menu
	this->gui = std::make_unique<Menu>(true);
	this->state = mainMenu;
}

void Game::startGame()
{
	//reseting vectors of entity and bullets
	this->entities.clear();
	this->bullets.clear();
	//initialize timers of spawn
	this->spawningEnmyTimer["SLIME"] = 3.f;
	this->spawningEnmyTimer["BLUE"] = 0.f;
	this->spawningEnmyTimer["PINK"] = 0.f;
	this->spawningEnmyTimer["SKELETON"] = 0.f;

	this->randomAngle = std::uniform_real_distribution<float>(-3.14f, 3.14f);

	//creating magic bowl and emplacing into vector
	std::unique_ptr<Entity> bowl(new MagicBowl());
	bowl->setPosition(static_cast<float>(this->window->getSize().x) / 2 - bowl->getGlobalBounds().width / 2,
		static_cast<float>(this->window->getSize().y) / 2 - bowl->getGlobalBounds().height / 2);
	this->entities.emplace_back(std::move(bowl));

	//creating character
	this->character = std::make_unique<Character>();
	this->character->setPosition(static_cast<float>(this->window->getSize().x) / 2,
		static_cast<float>(this->window->getSize().y) / 2);
	this->character->setScreenBounds(sf::FloatRect(0, 0, static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	//creating inforamtion about game: life, points and level of character
	this->gui = std::make_unique<GameInformation>(this->character->getHealth(),
		this->character->getPoints(),
		this->character->getLevel());
}

void Game::initBuffs()
{
	//setting state of game on choosing buff
	this->state = buffState;
	std::vector<int> numbers{ 0, 1, 2, 3, 4, 5 };
	//randomize buffs
	std::shuffle(numbers.begin(), numbers.end(), this->rd);
	this->gui = std::make_unique<Buffs>(std::vector<int>(numbers.begin(), numbers.begin() + 3));
}

sf::Vector2f Game::randomPosition()
{
	//return vector2f of random position
	float rdAngle = this->randomAngle(rd);
	return sf::Vector2f(static_cast<float>(this->window->getSize().x) / 2 + (static_cast<float>(this->window->getSize().x) / 2 - 100) * cos(rdAngle),
		static_cast<float>(this->window->getSize().y) / 2 + static_cast<float>((this->window->getSize().y) / 2 - 100) * sin(rdAngle));
}

void Game::spawnSlime()
{
	//creating slime and emplacing into vector
	std::unique_ptr<Entity> slime(new Slime);
	slime->setPosition(this->randomPosition());
	this->entities.emplace_back(std::move(slime));
}

void Game::spawnGhost(const std::string& type)
{
	//creating ghost and emplacing into vector
	std::unique_ptr<Entity> ghost(new Ghost(type));
	ghost->setPosition(this->randomPosition());
	this->entities.emplace_back(std::move(ghost));
}

void Game::spawnSkeleton()
{
	//creating skeleton and emplacing into vector
	std::unique_ptr<Entity> skeleton(new Skeleton(static_cast<float>(this->window->getSize().x) / 2, static_cast<float>(this->window->getSize().y) / 2));
	this->entities.emplace_back(std::move(skeleton));
}

void Game::updateSpawningEnemies()
{
	//updating timers of sprawning enemies
	for (auto& i : this->spawningEnmyTimer)
		i.second += this->dt;

	//checking if enemy can spawn
	if (this->spawningEnmyTimer["SLIME"] >= 4.f && this->character->getLevel() < 3)
	{
		this->spawnSlime();
		this->spawningEnmyTimer["SLIME"] = 0.f;
	}

	if (this->spawningEnmyTimer["BLUE"] >= 6.f && this->character->getLevel() >= 2)
	{
		this->spawnGhost("blue");
		this->spawningEnmyTimer["BLUE"] = 0.f;
	}
	if (this->spawningEnmyTimer["PINK"] >= 10.f && this->character->getLevel() >= 3)
	{
		this->spawnGhost("pink");
		this->spawningEnmyTimer["PINK"] = 0.f;
	}
	if (this->spawningEnmyTimer["SKELETON"] >= 6.f && this->character->getLevel() >= 5)
	{
		this->spawnSkeleton();
		this->spawningEnmyTimer["SKELETON"] = 0.f;
	}
}

void Game::updateCharacter()
{
	//Checking if character get new level
	if (this->character->newLevel())
	{
		//initialize choosing buffs
		this->character->levelUp();
		this->state = buffState;
		this->initBuffs();
	}
	
	//updating attack of character
	this->character->attack(mousePosition, this->bullets);
	
	//checking if character is alive
	if (this->character->getHealth() <= 0)
	{
		//return to main menu if character is dead
		this->state = mainMenu;
		this->gui = std::make_unique<Menu>(true);
	}
	//updating character
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
				Skeleton* skeleton = dynamic_cast<Skeleton*>(entity->get());
				//Updating skeleton
				if (skeleton != nullptr)
					skeleton->update(sf::Vector2f(this->character->getPosition().x + this->character->getGlobalBounds().width / 2,
						this->character->getPosition().y + this->character->getGlobalBounds().height / 2),
						this->bullets,
						this->dt);
				//updating other type enemy
				else
					entity->get()->update(sf::Vector2f(this->character->getPosition().x + this->character->getGlobalBounds().width / 2,
						this->character->getPosition().y + this->character->getGlobalBounds().height / 2), this->dt);
				
				//updating intersection between character and circle of entity
				this->character->circleIntersection(entity->get()->getCircleBounds());
				//checking if enemy hit character
				if (this->character->getHitboxBounds().intersects(entity->get()->getHitboxBounds()))
				{
					//changing health of character
					this->character->setHealthMinus(entity->get()->getDamage());
				}
				++entity;
			}

		}
	}
}


void Game::updateBullets()
{
	for (auto bullet = this->bullets.begin(); bullet != this->bullets.end();)
	{
		//updating position of bullet
		bullet->get()->update(dt);

		//chekcing if bullet gone out of screen and deleting it
		if (!bullet->get()->getGlobalBounds().intersects(sf::FloatRect(0, 0, static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y))))
		{
			bullet = this->bullets.erase(bullet);
		}
		//checking if enemy bullet hit character
		else if (bullet->get()->getHitboxBounds().intersects(this->character->getHitboxBounds()) && bullet->get()->getEnemyBullet())
		{
			//changing life of character and deleting bullet
			this->character->setHealthMinus(bullet->get()->getDamage());
			bullet = this->bullets.erase(bullet);
		}
		else
		{
			++bullet;
		}
	}
}

void Game::updateSfmlEvent()
{
	//checking if is closing window event
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
		//Updating menu
		menu->update(this->dt);

		//getting choosen option
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (this->state == pauseMenu)
			{
				switch (menu->getOption())
				{
				case 0:
					//unpause game
					this->state = game;
					this->gui = std::make_unique<GameInformation>(this->character->getHealth(),
						this->character->getPoints(),
						this->character->getLevel());
					break;
				case 1:
					//restart game
					this->state = game;
					this->startGame();
					break;
				case 2:
					//close window
					this->window->close();
				}

			}
			else if (this->state == mainMenu)
			{
				switch (menu->getOption())
				{
				case 0:
					//start game
					this->state = game;
					this->startGame();
					break;
				case 1:
					//close window
					this->window->close();
				}
			}
		}
	}
	else if (info != nullptr) 
	{
		//updating game info 
	info->update(this->character->getHealth(),
		this->character->getPoints(),
		this->character->getLevel());	
	}
	else if (buff != nullptr)
	{
		//updating buff state
		buff->update(this->dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->state == buffState)
		{
			//getting chosen buff
			switch (buff->getOption())
			{
			case 0:
				//character +10% velocity
				this->character->velocityBuff();
				break;
			case 1:
				//character +1 health
				this->character->setHealthPlus(1);
				break; 
			case 2:
				//character +1 damage
				this->character->damageBuff();
				break; 
			case 3:
				//character attack speed +25%
				this->character->attackSpeedBuff();
				break; 
			case 4:
				//additional bullet
				this->character->bulletBuff();
				break;
			case 5:
				//expanding all entities radius of circle
				for (auto& i : this->entities)
					i->expandRadiusCircle();
				break;
			}
			//return to game
			this->state = game;
			this->gui = std::make_unique<GameInformation>(this->character->getHealth(),
				this->character->getPoints(),
				this->character->getLevel());
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
	//updating delta time
	this->dt = this->dtClock.restart().asSeconds();
	//updating close window event
	this->updateSfmlEvent();

	//update game
	if (this->state == game)
	{
		this->updateSpawningEnemies();
		this->mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
		this->updateBullets();
		this->updateEntities();
		this->updateCharacter();
	}
	//updating gui
	this->updateGui();
}

void Game::renderGame()
{
	//rendering entities, bullets and character
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
	//draw game
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
	//game loop
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}
