#pragma once
#include "Animations.h"
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Hitbox : public sf::RectangleShape
{
private:
	//Variables
	sf::Sprite& sprite;
	float offsetX;
	float offsetY;

public:
	//Constructors / Destructors
	Hitbox(sf::Sprite& sprite, float offsetX_, float offsetY_, float width, float height);
	~Hitbox();
	
	//Public functions
	void uptade();
	void render(sf::RenderTarget& target);


};

