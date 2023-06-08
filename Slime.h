#pragma once
#include "Entity.h"

class Slime : public Entity
{
private:
	//Initialize functions
	void initStats();
	void initTexture();
	void initHitbox();
	void initAnimations();


public:
	//Constructors / Destructors
	Slime();
	~Slime();

	//Public functions
	void update(const sf::Vector2f& direction,const float& dt);
};

