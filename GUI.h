#pragma once
#include "Hitbox.h"

class GUI
{
protected:
	//Variables
	std::vector<sf::Text> text;
	std::vector<sf::Sprite> sprites;
	std::unique_ptr<sf::Font> font;

	//Initialize functions
	virtual void initText();
	void initFont();

public:
	//Constructors / Destructors
	GUI();
	~GUI();

	//Public functions
	virtual void update(const float& dt);
	
	virtual void render(sf::RenderTarget& target);
};

