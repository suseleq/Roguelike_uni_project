#include "Bullet.h"

void Bullet::initTexture()
{
	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/bullet.png");
	this->setTexture(*this->texture);
	this->setScale(0.5f, 0.5f);
}

void Bullet::initHitbox()
{
	this->hitbox = std::make_unique<Hitbox>(*this, 5, 5, 8, 8);
}

Bullet::Bullet()
{
}

Bullet::Bullet(float velocity_, bool enemy_, const sf::Vector2f& direction_)
	: velocity(velocity_), enemy(enemy_), direction(direction_)
{
	this->initTexture();
	this->initHitbox();
}

Bullet::~Bullet()
{
}

sf::FloatRect Bullet::getHitboxBounds()
{
	return this->hitbox->getGlobalBounds();
}

const bool Bullet::getEnemyBullet() const
{
	return this->enemy;
}

void Bullet::uptade(const float& dt)
{
	this->move(this->direction.x * dt * this->velocity, 
		this->direction.y * dt * this->velocity);
	this->hitbox->uptade();
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(*this);
}
