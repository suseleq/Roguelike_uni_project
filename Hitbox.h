#pragma once
#include "Animations.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Hitbox : public sf::RectangleShape
{
private:

	sf::Sprite& sprite;

	float offsetX;
	float offsetY;

public:
	Hitbox(sf::Sprite& sprite, float offsetX_, float offsetY_, float width, float height);

	~Hitbox();

	void uptade();
	void render(sf::RenderTarget& target);


};

