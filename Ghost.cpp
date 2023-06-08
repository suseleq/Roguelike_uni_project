#include "Ghost.h"

//Initialize functions
void Ghost::initStats(const std::string& type)
{
	//initialize stats depends on type of ghost
	this->damage = 2;
	this->health = 3;
	if (type == "pink")
	{
		this->velocity = 200.f;
		this->points = 30;
	}
	else
	{
		this->velocity = 100.f;
		this->points = 20;
	}
}

void Ghost::initTexture(const std::string& type)
{
	//initialize texture depends on type of ghost and setting on sprite

	this->texture = std::make_unique<sf::Texture>();
	if (type == "pink")
	{
		this->texture->loadFromFile("./Textures/pinkGhost.png");
	}
	else
	{
		this->texture->loadFromFile("./Textures/blueGhost.png");
	}
	this->setTexture(*this->texture);
	this->setTextureRect(sf::IntRect(0, 0, 32, 32));
	this->setScale(2.5, 2.5);

}

void Ghost::initHitbox()
{
	//initialize hitbox
	this->hitbox = std::make_unique<Hitbox>(*this, 32, 28, 18, 31);
	this->circle = std::make_unique<Circle>(*this, this->getGlobalBounds().width, this->getGlobalBounds().height, 40);
	this->circle->setFillColor(sf::Color(195, 255, 200, 50));
}

void Ghost::initAnimations()
{
	//initialize animations
	this->animations["RUN"] = std::make_unique<Animations>(*this, *this->texture, 4, 70.f, sf::IntRect(0, 0, 32, 32), 0, 32);
	this->animations["DAMAGE"] = std::make_unique<Animations>(*this, *this->texture, 4, 70.f, sf::IntRect(0, 32, 32, 32), 0, 32);
	this->animations["DEAD"] = std::make_unique<Animations>(*this, *this->texture, 4, 40.f, sf::IntRect(0, 64, 32, 32), 0, 32);
}

//Constructors / Destructors
Ghost::Ghost(const std::string& type)
{
	//initialize variables
	this->initStats(type);
	this->initTexture(type);
	this->initHitbox();
	this->initAnimations();
}

Ghost::~Ghost()
{
}

//Public functions

void Ghost::update(const sf::Vector2f& direction, const float& dt)
{
	//Move toward character
	sf::Vector2f characterDirection = this->normalizeVector(direction);
	this->move(this->velocity * characterDirection.x * dt, this->velocity * characterDirection.y * dt);
	//Updating animation, hitbox, circle
	this->animations["RUN"]->makeAnimation(dt);
	this->circle->uptade();
	this->hitbox->uptade();
}
