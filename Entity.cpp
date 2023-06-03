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

sf::Vector2f Entity::normalizeVector(const sf::Vector2f& direction)
{
	sf::Vector2f result(direction.x - this->getPosition().x - this->getGlobalBounds().width / 2,
		direction.y - this->getPosition().y - this->getGlobalBounds().height / 2);
	float length = sqrt(pow(result.x, 2) + pow(result.y, 2));
	result = sf::Vector2f(result.x / length, result.y / length);
	return result;
}

int Entity::getHealth() const
{
	return this->health;
}

void Entity::setHealth()
{
	this->health--;
}

void Entity::setHealthPlus(int health_)
{
	this->health += health_;
}

void Entity::setHealthMinus(int health_)
{
	this->health -= health_;
}

void Entity::setDamage(int damage_)
{
	this->damage += damage_;
}

int Entity::getDamage()
{
	return this->damage;
}


void Entity::update(const float& dt)
{
	if(this->circle != nullptr)
		this->circle->uptade();
}

void Entity::update(const sf::Vector2f& direction, const float& dt)
{
	if (this->circle != nullptr)
		this->circle->uptade();
}


void Entity::setIsMoving(bool moving)
{
	this->isMoving = moving;
}

bool Entity::getIsMoving()
{
	return this->isMoving;
}

sf::FloatRect Entity::getCircleBounds()
{
	if (this->circle != nullptr)
	{
		return this->circle->getGlobalBounds();
	}
	return sf::FloatRect(0, 0, 0, 0);
}

sf::FloatRect Entity::getHitboxBounds()
{
	if (this->hitbox != nullptr)
	{
		return this->hitbox->getGlobalBounds();
	}
	return sf::FloatRect(0, 0, 0, 0);
}

void Entity::render(sf::RenderTarget& target)
{
	if (this->circle != nullptr)
	{
		this->circle->render(target);
	}
	
	target.draw(*this);
	/*if (this->hitbox != nullptr)
	{
		this->hitbox->render(target);
	}
	*/
}
