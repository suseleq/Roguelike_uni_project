#include "Slime.h"

//Initialize functions

void Slime::initStats()
{
	//Initialize stats
	this->health = 1;
	this->damage = 1;
	this->velocity = 100.f;
	this->points = 10;
}

void Slime::initTexture()
{
	//initialize texture and setting on sprite
	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/slime.png");
	this->setTexture(*this->texture);
	this->setTextureRect(sf::IntRect(0, 0, 16, 16));
	this->setScale(2.5, 2.5);
}

void Slime::initHitbox()
{
	//Initialize hitbox and circle
	this->hitbox = std::make_unique<Hitbox>(*this, 10, 18, 24, 14);
	this->circle = std::make_unique<Circle>(*this, this->getGlobalBounds().width, this->getGlobalBounds().height, 50);
	this->circle->setFillColor(sf::Color(195, 255, 200, 50));
}

void Slime::initAnimations()
{
	//Initialize animations
	this->animations["IDLE"] = std::make_unique<Animations>(*this, *this->texture, 6, 30.f, sf::IntRect(0, 0, 16, 16), 0, 16);
	this->animations["RUN"] = std::make_unique<Animations>(*this, *this->texture, 6, 30.f, sf::IntRect(0, 16, 16, 16), 0, 16);
}

//Constructors / Destructors

Slime::Slime()
{
	//Init variables
	this->initStats();
	this->initTexture();
	this->initHitbox();
	this->initAnimations();
}

Slime::~Slime()
{
}

//Public functions

void Slime::update(const sf::Vector2f& direction, const float& dt)
{
	//Move toward character
	sf::Vector2f characterDirection = this->normalizeVector(direction);
	this->move(this->velocity * characterDirection.x * dt, this->velocity * characterDirection.y * dt);
	//Updating animation, hitbox, circle
	this->animations["RUN"]->makeAnimation(dt);
	this->circle->uptade();
	this->hitbox->uptade();
}
