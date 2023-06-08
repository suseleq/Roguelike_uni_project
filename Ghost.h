#pragma once
#include "Entity.h"

class Ghost : public Entity
{
private:
	//Initialize functions
	void initStats(const std::string& type);
	void initTexture(const std::string& type);
	void initHitbox();
	void initAnimations();


public:
	//Constructors / Destructors
	Ghost(const std::string& type);
	~Ghost();

	//Public functions
	void update(const sf::Vector2f& direction, const float& dt);

};

