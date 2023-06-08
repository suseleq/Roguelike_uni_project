#pragma once
#include "Hitbox.h"

class GUI
{
protected:
	//Variables
	std::vector<sf::Text> text;
	std::vector<std::pair<sf::Sprite, int>> sprites;
	std::unique_ptr<sf::Font> font;
	std::unique_ptr<sf::Texture> texture;
	float delayTime;
	bool changeOption;
	int currentOption;


	//Initialize functions
	void initFont();
	

public:
	//Constructors / Destructors
	GUI();
	virtual ~GUI();

	//Public functions
	virtual void update(const float& dt);

	virtual int getOption() const;
	
	virtual void render(sf::RenderTarget& target);
};

