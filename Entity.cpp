#include "Entity.h"

//Initialize functions

void Entity::initStats()
{
	//Initialize stats
	this->isMoving = false;
	this->health = 0;
	this->velocity = 0.f;
	this->cooldownAttack = 0.f;
	this->maxCooldownAttack = 0.f;
	this->points = 0;
}

void Entity::initTexture()
{
	//Initialize texture and circle
	this->texture = nullptr;
	this->circle = nullptr;
}

void Entity::initHitbox()
{
	//Initialize hitbox
	this->hitbox = nullptr;
}

void Entity::initAnimations()
{

}

Entity::Entity()
{
	//Initialize variables
	this->initStats();
	this->initTexture();
	this->initHitbox();
	this->initAnimations();
}

//Constructors / Destructors

Entity::Entity(const std::string& path)
{
	this->initStats();
	this->initHitbox();
	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/" + path + ".png");
	this->setTexture(*this->texture);
}

Entity::~Entity()
{
}


//Setters
void Entity::setHealthPlus(int health_)
{
	//adding health
	this->health += health_;
}

void Entity::setHealthMinus(int health_)
{
	//minus health
	this->health -= health_;
}

void Entity::setDamage(int damage_)
{
	//adding damage
	this->damage += damage_;
}

void Entity::setIsMoving(bool moving)
{
	//set moving
	this->isMoving = moving;
}


//Getters

bool Entity::getIsMoving()
{
	//getting is entity move
	return this->isMoving;
}


int Entity::getHealth() const
{
	//getting health of entity
	return this->health;
}


int Entity::getDamage() const
{
	//getting damage of entity
	return this->damage;
}

int Entity::getPoints() const
{
	//getting points of entity
	return this->points;
}

sf::FloatRect Entity::getCircleBounds() const
{
	//getting bounds of circle
	if (this->circle != nullptr)
	{
		return this->circle->getGlobalBounds();
	}
	return sf::FloatRect(0, 0, 0, 0);
}

sf::FloatRect Entity::getHitboxBounds() const
{
	//getting bounds of hitbox
	if (this->hitbox != nullptr)
	{
		return this->hitbox->getGlobalBounds();
	}
	return sf::FloatRect(0, 0, 0, 0);
}

//Public functions

sf::Vector2f Entity::normalizeVector(const sf::Vector2f& direction)
{
	sf::Vector2f result(direction.x - this->getPosition().x - this->getGlobalBounds().width / 2,
		direction.y - this->getPosition().y - this->getGlobalBounds().height / 2);
	float length = sqrt(pow(result.x, 2) + pow(result.y, 2));
	result = sf::Vector2f(result.x / length, result.y / length);
	return result;
}

void Entity::update(const float& dt)
{
	//updating circle, hitbox and idle animation
	if(this->circle != nullptr)
		this->circle->uptade();
	if (this->animations["IDLE"] != nullptr)
	{
		this->animations["IDLE"]->makeAnimation(dt);
	}
	if (this->hitbox != nullptr)
		this->hitbox->uptade();

}

void Entity::update(const sf::Vector2f& direction, const float& dt)
{
}

void Entity::render(sf::RenderTarget& target)
{
	//draw sprite circle and hitbox
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
