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
	this->cooldownAttack = 0.f;
	this->maxCooldownAttack = 0.f;
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

void Entity::attack(sf::Vector2f& direction, std::vector<std::unique_ptr<Bullet>>& bullets)
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

void Entity::render(sf::RenderTarget& target)
{
	if (this->circle != nullptr)
	{
		this->circle->render(target);
	}
	
	target.draw(*this);
	if (this->hitbox != nullptr)
	{
		this->hitbox->render(target);
	}
}
