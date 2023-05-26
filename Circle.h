#pragma once
#include "Animations.h"

class Circle : public sf::CircleShape
{
private:
	sf::Sprite& sprite;
	
	float offsetX;
	float offsetY;


public:

	Circle(sf::Sprite& sprite, float offsetX_, float offsetY_, int radius);
	~Circle();

	void uptade();
	void render(sf::RenderTarget& target);



};

