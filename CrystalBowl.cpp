#include "CrystalBowl.h"

void CrystalBowl::initStats()
{
	this->circle = std::make_unique<Circle>(*this, this->getGlobalBounds().width, this->getGlobalBounds().height, 120);
	this->circle->setFillColor(sf::Color(195, 255, 200, 100));
}

void CrystalBowl::initTexture()
{
	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/magicBowl.png");
	this->setTexture(*this->texture);
	this->setTextureRect(sf::IntRect(0, 0, 32, 32));
	this->scale(1.5f, 1.5f);
}

void CrystalBowl::initAnimations()
{
	this->animations["IDLE"] = std::make_unique<Animations>(*this, *this->texture, 4, 50.f, sf::IntRect(0, 0, 32, 32), 0, 32);
}

CrystalBowl::CrystalBowl()
{
	this->initTexture();
	this->initAnimations();
	this->initStats();
}

CrystalBowl::~CrystalBowl()
{
}

void CrystalBowl::update(const float& dt)
{
	this->animations["IDLE"]->makeAnimation(dt);
	this->circle->uptade();
}
