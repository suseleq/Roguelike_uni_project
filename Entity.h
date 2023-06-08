#pragma once
#include "Animations.h"
#include "Circle.h"
#include "Hitbox.h"
#include "Bullet.h"
#include <vector>
#include <memory>
#include <map>


class Entity : public sf::Sprite
{
protected:
	
	//Variables
	std::unique_ptr<Circle> circle;
	std::unique_ptr<sf::Texture> texture;
	std::unique_ptr<Hitbox> hitbox;
	std::map<std::string, std::unique_ptr<Animations>> animations;

	int health;
	int damage;
	bool isMoving;
	float velocity;
	float maxCooldownAttack;
	float cooldownAttack;
	int points;

	//Initialize functions
	virtual void initStats();
	virtual void initTexture();
	virtual void initHitbox();
	virtual void initAnimations();


public:
	//Constructors / Destructors
	Entity();
	Entity(const std::string& path);
	virtual ~Entity();

	//Setters

	void setIsMoving(bool moving);
	void setHealthPlus(int health_);
	virtual void setHealthMinus(int health_);
	void setDamage(int damage_);

	//Getters
	bool getIsMoving();
	sf::FloatRect getCircleBounds() const;
	sf::FloatRect getHitboxBounds() const;
	int getHealth() const;
	int getDamage() const;
	int getPoints() const;
	
	//Public functions
	sf::Vector2f normalizeVector(const sf::Vector2f& direction);
	virtual void update(const float& dt);
	virtual void update(const sf::Vector2f& direction, const float& dt);
	virtual void render(sf::RenderTarget& target);
};

