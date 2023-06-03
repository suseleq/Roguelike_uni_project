#pragma once
#include "Hitbox.h"

class Menu
{
private:
	float delayTime;
	bool changeOption;
	int currentOption;
	std::vector<sf::Text> text;
	std::unique_ptr<sf::Font> font;
	
public:
	Menu(bool mainMenu);
	~Menu();

	void moveUp();
	void moveDown();

	void update(const float& dt);

	void render(sf::RenderTarget& target);
	int getOption();
};

