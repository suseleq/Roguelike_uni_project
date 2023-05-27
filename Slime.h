#pragma once
#include "Entity.h"

class Slime : public Entity
{

private:
	void initStats();
	void initTexture();
	void initHitbox();
	void initAnimations();


public:
	Slime();
	~Slime();

	
	void update(sf::Vector2f& direction,const float& dt);




};

