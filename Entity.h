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
	
	std::unique_ptr<Circle> circle;
	std::unique_ptr<sf::Texture> texture;
	std::unique_ptr<Hitbox> hitbox;
	std::map<std::string, std::unique_ptr<Animations>> animations;

	int health;
	bool isMoving;
	float velocity;
	float maxCooldownAttack;
	float cooldownAttack;



	virtual void initStats();
	virtual void initTexture();
	virtual void initHitbox();
	virtual void initAnimations();


public:
	Entity();
	Entity(const std::string& path);
	virtual ~Entity();

	//virtual void move(const float& dt, const sf::Vector2f& direction);
	//sf::Vector2f getPosition();
	void setIsMoving(bool moving);
	bool getIsMoving();

	sf::FloatRect getCircleBounds();
	sf::FloatRect getHitboxBounds();

	//void setPosition(const sf::Vector2f& position);
	virtual void attack(sf::Vector2f& direction, std::vector<std::unique_ptr<Bullet>>& bullets);
	
	virtual void update(const float& dt);
	virtual void update(const float& dt, const sf::Vector2f& direction);
	virtual void render(sf::RenderTarget& target);
};

