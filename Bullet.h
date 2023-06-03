#pragma once
#include "Hitbox.h"

class Bullet : public sf::Sprite
{
private:
	std::unique_ptr<sf::Texture> texture;
	std::unique_ptr<Hitbox> hitbox;

	float velocity;
	bool enemy;
	sf::Vector2f direction;

	void initTexture();
	void initHitbox();

public:
	Bullet();
	Bullet(float velocity_, bool enemy_,const sf::Vector2f& direction_);
	~Bullet();

	sf::FloatRect getHitboxBounds();
	const bool getEnemyBullet() const;
	void uptade(const float& dt);
	void render(sf::RenderTarget& target);

};

