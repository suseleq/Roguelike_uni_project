#pragma once
#include "Entity.h"

class Skeleton : public Entity
{
	float radiusA;
	float radiusB;
	float angle;

	std::random_device rd;
	std::uniform_real_distribution<float> randomAngle;

	void initStats();
	void initTexture();
	void initHitbox();
	void initAnimations();

	void moving(const float& dt);

public:
	Skeleton(float radiusA_, float radiusB_);
	~Skeleton();


	void update(const sf::Vector2f& direction, const float& dt);
	
};

