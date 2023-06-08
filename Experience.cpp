#include "Experience.h"

//Initialize functions
void Experience::initTexture()
{
	//Initialize texture
	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/experience.png");
	this->setTexture(*this->texture);
	this->setTextureRect(sf::IntRect(0, 0, 8, 8));
	this->scale(2.f, 2.f);
}

void Experience::initAnimations()
{
	//Initialize animations
	this->animations["IDLE"] = std::make_unique<Animations>(*this, *this->texture, 3, 80.f, sf::IntRect(0, 0, 8, 8), 0, 8);
}

void Experience::initHitbox()
{
	//Initialize hitbox
	this->hitbox = std::make_unique<Hitbox>(*this, 3, 3, 10, 10);
}

//Constructors / Destructors

Experience::Experience()
{
	//Initialize variables
	this->initTexture();
	this->initHitbox();
	this->initAnimations();
}

Experience::~Experience()
{
}
