#include "GUI.h"

void GUI::initText()
{
	this->text = std::vector<sf::Text>(6);
	this->text[0].setString("Life:");
	this->text[1].setString("0");
	this->text[2].setString("Points:");
	this->text[3].setString("0");
	this->text[4].setString("Level:");
	this->text[5].setString("0");


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

GUI::GUI()
{
	this->font = std::make_unique<sf::Font>();
	this->font->loadFromFile("./fonts/PixellettersFull.ttf");
}

GUI::GUI(int life, int points, int level)
{
	this->font = std::make_unique<sf::Font>();
	this->font->loadFromFile("./fonts/PixellettersFull.ttf");
	this->initText();
	this->text[1].setString(std::to_string(life));
	this->text[3].setString(std::to_string(level));
	this->text[5].setString(std::to_string(points));

}

GUI::~GUI()
{
}

void GUI::update(const float& dt)
{
}

void GUI::update(int life, int points, int level)
{
	this->text[1].setString(std::to_string(life));
	this->text[3].setString(std::to_string(level));
	this->text[5].setString(std::to_string(points));

}

void GUI::render(sf::RenderTarget& target)
{
	for (auto& i : this->text)
	{
		target.draw(i);
	}
}
