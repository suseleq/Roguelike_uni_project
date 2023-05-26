#include "Character.h"


void Character::initStats()
{
	this->health = 3;
	this->cooldownAttack = 200.f;
	this->maxCooldownAttack = 200.f;
	this->velocity = 200.f;
}

void Character::initTexture()
{
	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/character.png");
	this->setTexture(*this->texture);
	this->setTextureRect(sf::IntRect(0, 0, 32, 32));
	this->setScale(2.5, 2.5);

	this->setPosition(400, 300);
}

void Character::initHitbox()
{
	this->hitbox = std::make_unique<Hitbox>(*this, 31, 25, 17, 36);
	this->circle = std::make_unique<Circle>(*this, this->getGlobalBounds().width, this->getGlobalBounds().height, 60);
	this->circle->setFillColor(sf::Color(96, 161, 101, 110));
}

void Character::initAnimations()
{
	this->animations["IDLE"] = std::make_unique<Animations>(*this, *this->texture, 4, 70.f, sf::IntRect(0, 0, 32, 32), 0, 32);
	this->animations["RUN"] = std::make_unique<Animations>(*this, *this->texture, 8, 20.f, sf::IntRect(0, 32, 32, 32), 0, 32);
	this->animations["DAMAGE"] = std::make_unique<Animations>(*this, *this->texture, 4, 40.f, sf::IntRect(0, 64, 32, 32), 0, 32);
	this->animations["DEAD"] = std::make_unique<Animations>(*this, *this->texture, 8, 20.f, sf::IntRect(0, 96, 32, 32), 0, 32);
}

void Character::moving(const float& dt)
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->isMoving = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{	
			this->move(this->velocity * dt * -1, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->move(this->velocity * dt, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->move(0, this->velocity * dt * -1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->move(0, this->velocity * dt);
		}
	}
	else
	{
		this->isMoving = false;
	}
}

void Character::attack(sf::Vector2f& directionMouse, std::vector<std::unique_ptr<Bullet>>& bullets)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->cooldownAttack >= this->maxCooldownAttack) 
	{
		sf::Vector2f direction(directionMouse.x - this->getPosition().x, directionMouse.y - this->getPosition().y);
		float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
		direction = sf::Vector2f(direction.x / length, direction.y / length);

		std::unique_ptr<Bullet> bullet(new Bullet(100.f, false, direction));
		bullet->setPosition(this->hitbox->getPosition().x + 5 * cos(atan2f(direction.y, direction.x)),
			this->hitbox->getPosition().y + 3 * sin(atan2f(direction.y, direction.x)));
		bullets.emplace_back(std::move(bullet));
		this->cooldownAttack = 0.f;
	}
}


Character::Character()
{
	this->initStats();
	this->initTexture();
	this->initHitbox();
	this->initAnimations();
}

Character::~Character()
{
}

void Character::update(const float& dt)
{
	if(this->cooldownAttack < this->maxCooldownAttack)
	{
		this->cooldownAttack += 100 * dt;
	}

	this->moving(dt);
	if (this->isMoving)
		this->animations["RUN"]->makeAnimation(dt);
	else
		this->animations["IDLE"]->makeAnimation(dt);

	this->hitbox->uptade();
	this->circle->uptade();
}



