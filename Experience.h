#pragma once
#include "Entity.h"


class Experience : public Entity
{
private:
	void initTexture();
	void initAnimations();
	void initHitbox();

public:
	Experience();
	~Experience();
};

