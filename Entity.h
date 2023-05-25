#pragma once
#include "Animations.h"
#include <memory>
#include "Hitbox.h"
#include <map>

class Entity : public sf::Sprite
{
protected:
	
	std::unique_ptr<sf::CircleShape> circle;
	std::unique_ptr<sf::Texture> texture;
	std::unique_ptr<Hitbox> hitbox;
	std::map<std::string, std::unique_ptr<Animations>> animations;

	int health;
	bool isMoving;
	float velocity;

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

	//void setPosition(const sf::Vector2f& position);
	virtual void attack(const sf::Vector2f& direction);
	
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
};

