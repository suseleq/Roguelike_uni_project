#pragma once
#include "Animations.h"

class Hitbox
{
private:

	sf::Sprite& sprite;
	sf::RectangleShape hitboxShape;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;

public:
	Hitbox(sf::Sprite& sprite,
		float offsetX_, float offsetY_,
		float width, float height);

	~Hitbox();

	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBound() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	void setPosition(const sf::Vector2f& position);

	bool intersects(const sf::FloatRect& rect);

	void uptade();
	void render(sf::RenderTarget& target);


};

