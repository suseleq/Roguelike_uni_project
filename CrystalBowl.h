#pragma once
#include "Entity.h"

class CrystalBowl : public Entity
{
private:
	virtual void initStats() override;
	virtual void initTexture() override;
	virtual void initAnimations() override;

public:
	CrystalBowl();
	~CrystalBowl();

	virtual void update(const float& dt) override;
	virtual void update(const sf::Vector2f& direction, const float& dt) override;

};

