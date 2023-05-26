#include "Character.h"

void Character::initStats()
{
	this->health = 3;
	this->velocity = 100.f;
}

void Character::initTexture()
{
	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/character.png");
	this->setTexture(*this->texture);
	this->setTextureRect(sf::IntRect(0, 0, 32, 32));
	this->setScale(3, 3);

	this->setPosition(400, 300);
}

void Character::initHitbox()
{
	this->hitbox = std::make_unique<Hitbox>(*this, 37, 33, 20, 35);
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
	if (this->isMoving)
		this->animations["RUN"]->makeAnimation(dt);
	else
		this->animations["IDLE"]->makeAnimation(dt);

	this->hitbox->uptade();
	this->circle->uptade();
}



