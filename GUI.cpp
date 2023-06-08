#include "GUI.h"

//Initialize functions

void GUI::initText()
{
	//Initilize text
	this->text = std::vector<sf::Text>(6);
	this->text[0].setString("Life:");
	this->text[1].setString("0");
	this->text[2].setString("Points:");
	this->text[3].setString("0");
	this->text[4].setString("Level:");
	this->text[5].setString("0");

	//Setting position of text
	float x{ 100.f }, y{ 10.f };
	for (auto& i : this->text)
	{
		i.setFont(*this->font);
		i.setFillColor(sf::Color::White);
		i.setCharacterSize(32);
		i.setPosition(x, y);
		x += 100.f;
	}
}

void GUI::initFont()
{
	//Initialize font
	this->font = std::make_unique<sf::Font>();
	this->font->loadFromFile("./fonts/PixellettersFull.ttf");
}

//Constructors / Destructors

GUI::GUI()
{
	//Init font
	this->initFont();
}

GUI::GUI(int life, int points, int level)
{
	//Initialize font and text of GUI
	this->initFont();
	this->initText();
	this->text[1].setString(std::to_string(life));
	this->text[3].setString(std::to_string(points));
	this->text[5].setString(std::to_string(level));

}

GUI::~GUI()
{
}

//Public functions

void GUI::update(const float& dt)
{
}

void GUI::update(int life, int points, int level)
{
	//Update information about health, points and level of character
	this->text[1].setString(std::to_string(life));
	this->text[3].setString(std::to_string(points));
	this->text[5].setString(std::to_string(level));

}

void GUI::render(sf::RenderTarget& target)
{
	//Draw text of gui
	for (auto& i : this->text)
	{
		target.draw(i);
	}
}
