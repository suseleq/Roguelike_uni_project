#pragma once
#include "Entity.h"

class Skeleton : public Entity
{
	float radiusA;
	float radiusB;


	void initStats(float radiusA_, float radiusB_);
	void initTexture();
	void initHitbox();
	void initAnimations();


public:
	Skeleton(float radiusA_, float radiusB_);
	~Skeleton();


	void update(const sf::Vector2f& direction, const float& dt);

};

