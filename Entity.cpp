#include "Entity.h"

void Entity::initStats()
{
}

void Entity::initTexture()
{
}

void Entity::initHitbox()
{
}

void Entity::initAnimations()
{
}

Entity::Entity()
{
	this->isMoving = false;
	this->circle = nullptr;
	this->health = 0;
	this->velocity = 0.f;
	this->hitbox = nullptr;
	this->texture = nullptr;
}



Entity::Entity(const std::string& path)
{
	this->health = 0;
	this->velocity = 0.f;
	this->isMoving = false;
	this->circle = nullptr;
	this->hitbox = nullptr;

	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/" + path + ".png");
	this->setTexture(*this->texture);
}

Entity::~Entity()
{
}

void Entity::update(const float& dt)
{
}


void Entity::setIsMoving(bool moving)
{
	this->isMoving = moving;
}

bool Entity::getIsMoving()
{
	return this->isMoving;
}


void Entity::attack(const sf::Vector2f& direction)
{
}

void Entity::render(sf::RenderTarget& target)
{
	if (this->circle != nullptr)
	{
		target.draw(*this->circle);
	}
	target.draw(*this);
}
