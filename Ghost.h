#pragma once
#include "Entity.h"

class Ghost : public Entity
{
private:
	void initStats();
	void initTexture();
	void initHitbox();
	void initAnimations();


public:
	Ghost();
	~Ghost();


	void update(const sf::Vector2f& direction, const float& dt);

};

