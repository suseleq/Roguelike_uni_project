#include "Entity.h"

Entity::Entity(int health_, int velocity_) :
	health(health_), velocity(velocity_)
{
}

Entity::~Entity()
{
}

void Entity::update(const float& dt)
{
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
