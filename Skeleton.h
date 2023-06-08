#pragma once
#include "Entity.h"

class Skeleton : public Entity
{
	//Variables
	float radiusA;
	float radiusB;
	float angle;

	std::random_device rd;
	std::uniform_real_distribution<float> randomAngle;

	//Initialize functions
	void initStats();
	void initTexture();
	void initHitbox();
	void initAnimations();

	//Private functions
	void moving(const float& dt);
	void attack(const sf::Vector2f& direction, std::vector<std::unique_ptr<Bullet>>& bullets, const float& dt);

public:
	//Constructors / Destructors
	Skeleton(float radiusA_, float radiusB_);
	~Skeleton();

	//Public functions
	void update(const sf::Vector2f& direction, std::vector<std::unique_ptr<Bullet>>& bullets,const float& dt);
	
};

