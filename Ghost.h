#pragma once
#include "Entity.h"

class Ghost : public Entity
{
private:
	void initStats(const std::string& type);
	void initTexture(const std::string& type);
	void initHitbox();
	void initAnimations();


public:
	Ghost(const std::string& type);
	~Ghost();


	void update(const sf::Vector2f& direction, const float& dt);

};

