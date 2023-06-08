#pragma once
#include "Entity.h"

class Experience : public Entity
{
private:
	//Initialize functions
	void initTexture();
	void initAnimations();
	void initHitbox();

public:
	//Constructors / Destructors
	Experience();
	~Experience();
};

