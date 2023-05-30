#include "Slime.h"

void Slime::initStats()
{
	this->health = 1;
	this->velocity = 100.f;
}

void Slime::initTexture()
{
	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/slime.png");
	this->setTexture(*this->texture);
	this->setTextureRect(sf::IntRect(0, 0, 32, 32));
	this->setScale(2.5, 2.5);

	this->setPosition(400, 300);
}

void Slime::initHitbox()
{
	this->hitbox = std::make_unique<Hitbox>(*this, 10, 18, 24, 14);
	this->circle = std::make_unique<Circle>(*this, this->getGlobalBounds().width, this->getGlobalBounds().height, 60);
	this->circle->setFillColor(sf::Color(195, 255, 200, 50));
}

void Slime::initAnimations()
{
	this->animations["IDLE"] = std::make_unique<Animations>(*this, *this->texture, 6, 30.f, sf::IntRect(0, 0, 16, 16), 0, 16);
	this->animations["RUN"] = std::make_unique<Animations>(*this, *this->texture, 6, 30.f, sf::IntRect(0, 16, 16, 16), 0, 16);
}

Slime::Slime()
{
	this->initStats();
	this->initTexture();
	this->initHitbox();
	this->initAnimations();
}

Slime::~Slime()
{
	this->initStats();
	this->initTexture();
	this->initHitbox();
	this->initAnimations();
}

void Slime::update(const sf::Vector2f& direction, const float& dt)
{
	sf::Vector2f characterDirection = this->normalizeVector(direction);
	this->move(this->velocity * characterDirection.x * dt, this->velocity * characterDirection.y * dt);
	this->animations["RUN"]->makeAnimation(dt);
	this->circle->uptade();
	this->hitbox->uptade();
}
