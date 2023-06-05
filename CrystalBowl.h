#pragma once
#include "Entity.h"

class CrystalBowl : public Entity
{
private:
	//Initialize functions
	void initStats();
	void initTexture();
	void initAnimations();

public:
	//Constructors / Destructors
	CrystalBowl();
	~CrystalBowl();

	//public functions
	void update(const float& dt);
	

};

