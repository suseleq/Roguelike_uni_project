#include "Skeleton.h"

void Skeleton::initStats()
{
	this->health = 5;
	this->damage = 3;
	this->randomAngle = std::uniform_real_distribution<float>(0, 3.14);
	this->velocity = 0.3f;
	this->angle = this->randomAngle(rd);
	this->points = 50;
}

void Skeleton::initTexture()
{
	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/skeleton.png");
	this->setTexture(*this->texture);
	this->setTextureRect(sf::IntRect(0, 0, 48, 48));
	this->setScale(1.5, 1.5);
}

void Skeleton::initHitbox()
{
	this->hitbox = std::make_unique<Hitbox>(*this, 26, 32, 15, 34);
	this->circle = std::make_unique<Circle>(*this, this->getGlobalBounds().width, this->getGlobalBounds().height, 40);
	this->circle->setFillColor(sf::Color(195, 255, 200, 50));
}

void Skeleton::initAnimations()
{
	this->animations["RUN"] = std::make_unique<Animations>(*this, *this->texture, 4, 70.f, sf::IntRect(0, 0, 48, 48), 0, 48);
}

void Skeleton::moving(const float& dt)
{
	this->setPosition(this->radiusA + (this->radiusA - 100) * cos(angle),
		this->radiusB + (this->radiusB - 100) * sin(angle));
	this->angle += velocity * dt;
}

Skeleton::Skeleton(float radiusA_, float radiusB_) : radiusA(radiusA_), radiusB(radiusB_)
{
	this->initStats();
	this->initTexture();
	this->initHitbox();
	this->initAnimations();
}

Skeleton::~Skeleton()
{
}

void Skeleton::update(const sf::Vector2f& direction, const float& dt)
{
	this->animations["RUN"]->makeAnimation(dt);
	this->circle->uptade();
	this->hitbox->uptade();
	this->moving(dt);
}
