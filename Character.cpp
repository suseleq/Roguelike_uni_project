#include "Character.h"
#include <iostream>

void Character::initStats()
{
	this->canAttack = false;
	this->health = 3;
	this->cooldownAttack = 250.f;
	this->maxCooldownAttack = 250.f;
	this->velocity = 150.f;
	this->damage = 1;
	this->additionalBullets = 0;
	this->randomDirection = std::uniform_real_distribution<float>(-1.f, 1.f);
}

void Character::initTexture()
{
	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/character.png");
	this->setTexture(*this->texture);
	this->setTextureRect(sf::IntRect(0, 0, 32, 32));
	this->setScale(2.5, 2.5);

	this->setPosition(400, 300);
}

void Character::initHitbox()
{
	this->hitbox = std::make_unique<Hitbox>(*this, 31, 25, 17, 36);
	this->circle = std::make_unique<Circle>(*this, this->getGlobalBounds().width, this->getGlobalBounds().height, 60);
	this->circle->setFillColor(sf::Color(96, 161, 101, 110));
}

void Character::initAnimations()
{
	this->animations["IDLE"] = std::make_unique<Animations>(*this, *this->texture, 4, 70.f, sf::IntRect(0, 0, 32, 32), 0, 32);
	this->animations["RUN"] = std::make_unique<Animations>(*this, *this->texture, 8, 20.f, sf::IntRect(0, 32, 32, 32), 0, 32);
	this->animations["DAMAGE"] = std::make_unique<Animations>(*this, *this->texture, 4, 40.f, sf::IntRect(0, 64, 32, 32), 0, 32);
	this->animations["DEAD"] = std::make_unique<Animations>(*this, *this->texture, 8, 20.f, sf::IntRect(0, 96, 32, 32), 0, 32);
}

void Character::moving(const float& dt)
{	
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

void Character::setScreenBounds(const sf::FloatRect& bounds)
{
	this->screenBounds = bounds;
}

void Character::circleIntersection(const sf::FloatRect& bounds)
{

	if (this->hitbox->getGlobalBounds().intersects(bounds))
	{
		this->canAttack = true;
	}
}

void Character::setCanAttack(bool cA)
{
	this->canAttack = cA;
}

void Character::damageBuff()
{
	this->damage++;
}

void Character::velocityBuff()
{
	this->velocity += this->velocity * 0.1;
}

void Character::attackSpeedBuff()
{
	this->maxCooldownAttack -= this->maxCooldownAttack * 0.25;
}

void Character::bulletBuff()
{
	this->additionalBullets++;
}

void Character::attack(sf::Vector2f& directionMouse, std::vector<std::unique_ptr<Bullet>>& bullets)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->cooldownAttack >= this->maxCooldownAttack && this->canAttack) 
	{
		sf::Vector2f direction = this->normalizeVector(directionMouse);
		std::unique_ptr<Bullet> bullet(new Bullet(100.f, false, direction));
		bullet->setPosition(this->getPosition().x + this->getGlobalBounds().width / 2, this->getPosition().y + this->getGlobalBounds().height / 2);
		bullets.emplace_back(std::move(bullet));
		for (size_t i = 0; i < this->additionalBullets; i++)
		{
			std::unique_ptr<Bullet> bullet(new Bullet(100.f, false, sf::Vector2f(this->randomDirection(rd), this->randomDirection(rd))));
			bullet->setPosition(this->getPosition().x + this->getGlobalBounds().width / 2, this->getPosition().y + this->getGlobalBounds().height / 2);
			bullets.emplace_back(std::move(bullet));
		}
		
		this->cooldownAttack = 0.f;
	}
}


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

void Character::update(const float& dt)
{
	this->canAttack = false;
	if(this->cooldownAttack < this->maxCooldownAttack)
	{
		this->cooldownAttack += 100 * dt;
	}

	this->moving(dt);
	if (this->isMoving)
		this->animations["RUN"]->makeAnimation(dt);
	else
		this->animations["IDLE"]->makeAnimation(dt);

	this->hitbox->uptade();
	this->circle->uptade();
}



