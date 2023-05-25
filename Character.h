#pragma once
#include "Entity.h"

class Character : public Entity
{
private:
	void initStats();
	void initTexture();
	void initHitbox();
	void initAnimations();
public:
	Character();
	~Character();

	void update(const float& dt);
};

