#pragma once
#include <random>
#include "Entity.h"

class Character : public Entity
{
private:
	bool canAttack;
	int additionalBullets;
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
	void setCanAttack(bool cA);
	void damageBuff();
	void velocityBuff();
	void attackSpeedBuff();
	void bulletBuff();
	void attack(sf::Vector2f& direction, std::vector<std::unique_ptr<Bullet>>& bullets);
	void update(const float& dt);
};

