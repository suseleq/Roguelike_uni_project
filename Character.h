#pragma once
#include <random>
#include "Entity.h"

class Character : public Entity
{
private:
	//Variables
	bool canAttack;
	int additionalBullets;
	int level;
	int experience;
	int nextLevelExp;
	float immuneTimer;
	float maxImmuneTime;
	sf::FloatRect screenBounds;

	std::random_device rd;
	std::uniform_real_distribution<float> randomDirection;

	//Initialize functions
	void initStats();
	void initTexture();
	void initHitbox();
	void initAnimations();

	//Private functions
	void moving(const float& dt);
	int calulculateExp();

public:
	//Consturctors / Destructors
	Character();
	~Character();

	//Setters / Getters
	void setScreenBounds(const sf::FloatRect& bounds);
	int getLevel();
	void setHealthMinus(int health_);

	//Buff functions
	void damageBuff();
	void velocityBuff();
	void attackSpeedBuff();
	void bulletBuff();

	//Public functions
	bool newLevel() const;
	void levelUp();
	void addExperience();
	void circleIntersection(const sf::FloatRect& bounds);
	void addPoints(int points_);
	void attack(sf::Vector2f& direction, std::vector<std::unique_ptr<Bullet>>& bullets);
	void update(const float& dt);
};

