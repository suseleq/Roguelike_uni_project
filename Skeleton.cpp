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
	//Initialize texture and setting on sprite
	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/skeleton.png");
	this->setTexture(*this->texture);
	this->setTextureRect(sf::IntRect(0, 0, 48, 48));
	this->setScale(1.5, 1.5);
}

void Skeleton::initHitbox()
{
	//Initialize hitbox and circle
	this->hitbox = std::make_unique<Hitbox>(*this, 26, 32, 15, 34);
	this->circle = std::make_unique<Circle>(*this, this->getGlobalBounds().width, this->getGlobalBounds().height, 60);
	this->circle->setFillColor(sf::Color(195, 255, 200, 50));
}

void Skeleton::initAnimations()
{
	//initialize animations
	this->animations["RUN"] = std::make_unique<Animations>(*this, *this->texture, 4, 70.f, sf::IntRect(0, 0, 48, 48), 0, 48);
}

//Private functions

void Skeleton::moving(const float& dt)
{
	//uptade positon of skeleton
	this->setPosition(this->radiusA + (this->radiusA - 100) * cos(angle),
		this->radiusB + (this->radiusB - 100) * sin(angle));
	this->angle += velocity * dt;
}

void Skeleton::attack(const sf::Vector2f& direction, std::vector<std::unique_ptr<Bullet>>& bullets, const float &dt)
{
	//calculate vector of direction of bullet
	sf::Vector2f direction_ = this->normalizeVector(direction);
	//checking if can attack
	if (this->cooldownAttack >= this->maxCooldownAttack)
	{
		//creating bullet and emplace to vector of bulletss
		std::unique_ptr<Bullet> bullet(new Bullet(this->damage, 100.f, true, direction_));
		bullet->setPosition(this->getPosition().x + this->getGlobalBounds().width / 2, this->getPosition().y + this->getGlobalBounds().height / 2);
		bullets.emplace_back(std::move(bullet));
		this->cooldownAttack = 0.f;
	}
	else 
	{
		//updating cooldown of attack
		this->cooldownAttack += 100 * dt;
	}
}

//Constructors / Destructors

Skeleton::Skeleton(float radiusA_, float radiusB_) : radiusA(radiusA_), radiusB(radiusB_)
{
	//initialize variables
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
	//updating hitbox, circle, animation, movement and attack
	this->animations["RUN"]->makeAnimation(dt);
	this->circle->uptade();
	this->hitbox->uptade();
	this->moving(dt);
	this->attack(direction, bullets, dt);
}
