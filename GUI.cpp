#include "GUI.h"

//Initialize functions

void GUI::initFont()
{
	//Initialize font
	this->font = std::make_unique<sf::Font>();
	this->font->loadFromFile("./fonts/PixellettersFull.ttf");
}

//Constructors / Destructors

GUI::GUI()
{
	delayTime = 0.f;
	changeOption = false;
	currentOption = 0;
	this->font = nullptr;
	this->texture = nullptr;
}

GUI::~GUI()
{
}


//Public functions


void GUI::update(const float& dt)
{
}

int GUI::getOption() const
{
	//getting option
	return this->currentOption;
}


void GUI::render(sf::RenderTarget& target)
{
	//Draw text of gui
	for (auto& i : this->text)
	{
		target.draw(i);
	}
}
