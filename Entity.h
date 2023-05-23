#pragma once
#include "Animations.h"
#include <memory>

class Entity
{
protected:
	sf::Sprite sprite;
	int health;
	int velocity;

	virtual void initTexture() = 0;
	virtual void initStats() = 0;

public:
	Entity(int health_, int velocity_);
	virtual ~Entity();

	virtual void update(const float &dt);
	void render(sf::RenderTarget& target);
};

