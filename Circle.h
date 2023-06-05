#pragma once
#include "Animations.h"

class Circle : public sf::CircleShape
{
private:
	//Variables
	sf::Sprite& sprite;
	
	float offsetX;
	float offsetY;


public:
	//Constructors / Destructors
	Circle(sf::Sprite& sprite, float offsetX_, float offsetY_, int radius);
	~Circle();

	//Public functions
	void uptade();
	void render(sf::RenderTarget& target);



};

