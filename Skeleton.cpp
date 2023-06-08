#include "Skeleton.h"

//Initialize functions

void Skeleton::initStats()
{
	//initialize stats
	this->maxCooldownAttack = 300.f;
	this->cooldownAttack = 200.f;
	this->health = 5;
	this->damage = 3;
	this->randomAngle = std::uniform_real_distribution<float>(-3.14, 3.14);
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

//Private functions

void Skeleton::moving(const float& dt)
{
	this->setPosition(this->radiusA + (this->radiusA - 100) * cos(angle),
		this->radiusB + (this->radiusB - 100) * sin(angle));
	this->angle += velocity * dt;
}

void Skeleton::attack(const sf::Vector2f& direction, std::vector<std::unique_ptr<Bullet>>& bullets, const float &dt)
{
	sf::Vector2f direction_ = this->normalizeVector(direction);
	if (this->cooldownAttack >= this->maxCooldownAttack)
	{
		std::unique_ptr<Bullet> bullet(new Bullet(this->damage, 100.f, true, direction_));
		bullet->setPosition(this->getPosition().x + this->getGlobalBounds().width / 2, this->getPosition().y + this->getGlobalBounds().height / 2);
		bullets.emplace_back(std::move(bullet));
		this->cooldownAttack = 0.f;
	}
	else 
	{
		this->cooldownAttack += 100 * dt;
	}
}

//Constructors / Destructors

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

//Public function

void Skeleton::update(const sf::Vector2f& direction, std::vector<std::unique_ptr<Bullet>>& bullets,const float& dt)
{
	this->animations["RUN"]->makeAnimation(dt);
	this->circle->uptade();
	this->hitbox->uptade();
	this->moving(dt);
	this->attack(direction, bullets, dt);
}
