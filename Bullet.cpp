#include "Bullet.h"

//Initialize functions

void Bullet::initTexture(bool enemy)
{
	//initialize texture depends on if it is enemy's bullet and setting on sprite
	this->texture = std::make_unique<sf::Texture>();
	if (enemy)
	{
		this->texture->loadFromFile("./Textures/bulletEnemy.png");
	}
	else
	{
		this->texture->loadFromFile("./Textures/bullet.png");
	}
	this->setTexture(*this->texture);
	this->setScale(0.5f, 0.5f);
}

void Bullet::initHitbox()
{
	//initialize hitbox
	this->hitbox = std::make_unique<Hitbox>(*this, 5, 5, 8, 8);
}

//Constructors / Destructors

Bullet::Bullet(int damage_, float velocity_, bool enemy_, const sf::Vector2f& direction_)
	: damage(damage_), velocity(velocity_), enemy(enemy_), direction(direction_)
{
	//initialize variables
	this->initTexture(enemy);
	this->initHitbox();
}

Bullet::~Bullet()
{
}

//Public functions

sf::FloatRect Bullet::getHitboxBounds()
{
	//return bounds of hitbox
	return this->hitbox->getGlobalBounds();
}

const bool Bullet::getEnemyBullet() const
{
	//return if enemy's bullet
	return this->enemy;
}

const int Bullet::getDamage() const
{
	//getting damege of bullet
	return this->damage;
}

void Bullet::setDamage(int damage_)
{
	//setting damage of bullet
	this->damage = damage_;
}

void Bullet::update(const float& dt)
{
	//updating position and hitbox
	this->move(this->direction.x * dt * this->velocity, 
		this->direction.y * dt * this->velocity);
	this->hitbox->uptade();
}

void Bullet::render(sf::RenderTarget& target)
{
	//draw bullet
	target.draw(*this);
}
