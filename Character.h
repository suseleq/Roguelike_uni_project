#pragma once
#include <random>
#include "Entity.h"

class Character : public Entity
{
private:
	bool canAttack;
	int additionalBullets;
	int level;
	sf::FloatRect screenBounds;

	std::random_device rd;
	std::uniform_real_distribution<float> randomDirection;

	void initStats();
	void initTexture();
	void initHitbox();
	void initAnimations();

	void moving(const float& dt);

public:
	Character();
	~Character();

	void setScreenBounds(const sf::FloatRect& bounds);
	void circleIntersection(const sf::FloatRect& bounds);
	int getLevel();
	void damageBuff();
	void velocityBuff();
	void attackSpeedBuff();
	void bulletBuff();
	void addPoints(int points_);
	void attack(sf::Vector2f& direction, std::vector<std::unique_ptr<Bullet>>& bullets);
	void update(const float& dt);
};

