#include "Character.h"

//Initialize functions


void Character::initStats()
{
	//Initialize stats
	this->canAttack = false;
	this->health = 5;
	this->cooldownAttack = 100.f;
	this->maxCooldownAttack = 100.f;
	this->velocity = 175.f;
	this->damage = 1;
	this->additionalBullets = 0;
	this->randomDirection = std::uniform_real_distribution<float>(-2.f, 2.f);
	this->points = 0;
	this->level = 1;
	this->experience = 0;
	this->nextLevelExp = calulculateExp();
	this->maxImmuneTime = 200.f;
	this->immuneTimer = 200.f;
}

void Character::initTexture()
{
	//Initialize texture and setting on sprite
	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/character.png");
	this->setTexture(*this->texture);
	this->setTextureRect(sf::IntRect(0, 0, 32, 32));
	this->setScale(2.5, 2.5);

	this->setPosition(400, 300);
}

void Character::initHitbox()
{
	////Initialize hitbox and circle
	this->hitbox = std::make_unique<Hitbox>(*this, 31, 25, 17, 36);
	this->circle = std::make_unique<Circle>(*this, this->getGlobalBounds().width, this->getGlobalBounds().height, 60);
	this->circle->setFillColor(sf::Color(96, 161, 101, 110));
}

void Character::initAnimations()
{
	//Initialize animations
	this->animations["IDLE"] = std::make_unique<Animations>(*this, *this->texture, 4, 70.f, sf::IntRect(0, 0, 32, 32), 0, 32);
	this->animations["RUN"] = std::make_unique<Animations>(*this, *this->texture, 8, 20.f, sf::IntRect(0, 32, 32, 32), 0, 32);
	this->animations["DAMAGE"] = std::make_unique<Animations>(*this, *this->texture, 4, 40.f, sf::IntRect(0, 64, 32, 32), 0, 32);
	this->animations["DEAD"] = std::make_unique<Animations>(*this, *this->texture, 8, 20.f, sf::IntRect(0, 96, 32, 32), 0, 32);
}

//Private functions

void Character::moving(const float& dt)
{	
	//Update movement of character

	//checking if key is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->isMoving = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->getGlobalBounds().left > this->screenBounds.left)
		{	
			this->move(this->velocity * dt * -1, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) 
			&& this->getGlobalBounds().left + this->getGlobalBounds().width < this->screenBounds.width)
		{
			this->move(this->velocity * dt, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->getGlobalBounds().top > this->screenBounds.top)
		{
			this->move(0, this->velocity * dt * -1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
			&& this->getGlobalBounds().top + this->getGlobalBounds().height < this->screenBounds.height)
		{
			this->move(0, this->velocity * dt);
		}
	}
	else
	{
		this->isMoving = false;
	}
}

int Character::calulculateExp()
{
	//Return needed eperience for the next level
	return 2 * this->level + 2;
}

//Consturctors / Destructors

Character::Character()
{
	this->initStats();
	this->initTexture();
	this->initHitbox();
	this->initAnimations();
}

Character::~Character()
{
}

//Setters / Getters

void Character::setScreenBounds(const sf::FloatRect& bounds)
{
	//Setting bounds of screen
	this->screenBounds = bounds;
}

int Character::getLevel()
{
	//getting level of character
	return this->level;
}

void Character::setHealthMinus(int health_)
{
	//substract value of health
	if (this->immuneTimer >= this->maxImmuneTime)
	{
		this->health -= health_;
		this->immuneTimer = 0.f;
	}
}

//Buff functions

void Character::damageBuff()
{
	//buff of damage character
	this->damage++;
}

void Character::velocityBuff()
{
	//buff of velocity character
	this->velocity += this->velocity * 0.1f;
}

void Character::attackSpeedBuff()
{
	//buff cooldown of attack
	this->maxCooldownAttack -= this->maxCooldownAttack * 0.25f;
}

void Character::bulletBuff()
{
	//add additional bullet
	this->additionalBullets++;
}


//Public functions

bool Character::newLevel() const
{
	//return true if character get levelup
	return this->experience >= this->nextLevelExp;
}

void Character::levelUp()
{
	//update level and experience of character
	this->level++;
	this->experience = 0;
	this->nextLevelExp = this->calulculateExp();
}

void Character::addExperience()
{
	//add experience of character
	this->experience++;
}

void Character::circleIntersection(const sf::FloatRect& bounds)
{
	//checking intersection with circle

	//getting vector beetwen character and circle
	sf::Vector2f v((this->getPosition().x + this->getGlobalBounds().width / 2) - (bounds.left + bounds.height / 2),
		(this->getPosition().y + this->getGlobalBounds().height / 2) - (bounds.top + bounds.height / 2));
	//calculate distance between character and center of circle
	float distance = sqrt(pow(v.x, 2) + pow(v.y, 2));
	//checking if character is in circle range
	if (distance <= bounds.height / 2)
	{
		this->canAttack = true;
	}
}

void Character::addPoints(int points_)
{
	//add points of character
	this->points += points_;
}

void Character::attack(sf::Vector2f& directionMouse, std::vector<std::unique_ptr<Bullet>>& bullets)
{
	//making attack

	//checking if character can attack
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->cooldownAttack >= this->maxCooldownAttack && this->canAttack) 
	{
		//creating bullet and emplace to vector of bullets
		sf::Vector2f direction = this->normalizeVector(directionMouse);
		std::unique_ptr<Bullet> bullet(new Bullet(this->damage, 150.f, false, direction));
		bullet->setPosition(this->getPosition().x + this->getGlobalBounds().width / 2, this->getPosition().y + this->getGlobalBounds().height / 2);
		bullets.emplace_back(std::move(bullet));
		
		//creating additional bullets and emplacing to vector of bullets
		for (size_t i = 0; i < this->additionalBullets; i++)
		{
			std::unique_ptr<Bullet> bullet(new Bullet(this->damage, 150.f, false, sf::Vector2f(this->randomDirection(rd), this->randomDirection(rd))));
			bullet->setPosition(this->getPosition().x + this->getGlobalBounds().width / 2, this->getPosition().y + this->getGlobalBounds().height / 2);
			bullets.emplace_back(std::move(bullet));
		}
		//reseting cooldown of attack
		this->cooldownAttack = 0.f;
	}
}


void Character::update(const float& dt)
{

	this->canAttack = false;

	if (this->immuneTimer < this->maxImmuneTime)
	{
		//update immune time after getting damage
		this->immuneTimer += 100 * dt;
	}
	if(this->cooldownAttack < this->maxCooldownAttack)
	{
		//update cooldown of attack
		this->cooldownAttack += 100 * dt;
	}

	//update moving of character
	this->moving(dt);
	if (this->isMoving)
		this->animations["RUN"]->makeAnimation(dt);
	else
		this->animations["IDLE"]->makeAnimation(dt);

	//updating hitbox and circle
	this->hitbox->uptade();
	this->circle->uptade();
}

