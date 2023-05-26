#pragma once
#include "Entity.h"

class Character : public Entity
{
private:
	void initStats();
	void initTexture();
	void initHitbox();
	void initAnimations();

	void moving(const float& dt);

	void attack(sf::Vector2f& direction, std::vector<std::unique_ptr<Bullet>>& bullets);
public:
	Character();
	~Character();

	void update(const float& dt);
};

