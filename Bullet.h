#pragma once
#include "Hitbox.h"

class Bullet : public sf::Sprite
{
private:
	//Variables
	std::unique_ptr<sf::Texture> texture;
	std::unique_ptr<Hitbox> hitbox;

	int damage;
	float velocity;
	bool enemy;
	sf::Vector2f direction;

	//Initialize functions
	void initTexture(bool enemy);
	void initHitbox();

public:
	//Constructors / Destructors
	Bullet(int damage, float velocity_, bool enemy_,const sf::Vector2f& direction_);
	~Bullet();

	//Getters and setters
	sf::FloatRect getHitboxBounds();
	const bool getEnemyBullet() const;
	const int getDamage() const;
	
	void setDamage(int damage);

	//Public functions
	void update(const float& dt);
	void render(sf::RenderTarget& target);

};

