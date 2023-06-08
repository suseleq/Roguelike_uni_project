#pragma once
#include "Entity.h"

class MagicBowl : public Entity
{
private:
	//Initialize functions
	void initStats();
	void initTexture();
	void initAnimations();

public:
	//Constructors / Destructors
	MagicBowl();
	~MagicBowl();

	//public functions
	void update(const float& dt);


};

