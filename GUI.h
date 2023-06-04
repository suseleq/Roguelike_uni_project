#pragma once
#include "Hitbox.h"

class GUI
{
protected:
	std::vector<sf::Text> text;
	std::unique_ptr<sf::Font> font;

	virtual void initText();
	

public:
	GUI();
	GUI(int life, int points, int level);
	~GUI();

	virtual void update(const float& dt);
	virtual void update(int life, int points, int level);
	void render(sf::RenderTarget& target);

};

