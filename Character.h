#pragma once
#include "Entity.h"

class Character : public Entity
{
private:
	bool canAttack;

	void initStats();
	void initTexture();
	void initHitbox();
	void initAnimations();

	void moving(const float& dt);

public:
	Character();
	~Character();

	void circleIntersection(const sf::FloatRect& bounds);
	void setCanAttack(bool cA);
	void attack(sf::Vector2f& direction, std::vector<std::unique_ptr<Bullet>>& bullets);
	void update(const float& dt);
};

