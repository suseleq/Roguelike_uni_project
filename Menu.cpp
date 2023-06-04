#include "Menu.h"

void Menu::initText(bool mainMenu)
{
	if (mainMenu)
	{
		this->text = std::vector<sf::Text>(2);
		this->text[0].setString("Play");
		this->text[1].setString("Quit");
	}
	else
	{
		this->text = std::vector<sf::Text>(3);
		this->text[0].setString("Return to game");
		this->text[1].setString("Restart");
		this->text[2].setString("Quit");
	}
	float x{ 100.f }, y{ 100.f };
	for (auto& i : this->text)
	{
		i.setFont(*this->font);
		i.setFillColor(sf::Color::White);
		i.setCharacterSize(100);
		i.setPosition(x, y);
		y += 200.f;
	}
	this->text[0].setFillColor(sf::Color::Red);

}

Menu::Menu(bool mainMenu)
{
	this->delayTime = 0.f;
	this->changeOption = true;
	this->currentOption = 0;
	this->initText(mainMenu);
}

Menu::~Menu()
{
}

void Menu::moveUp()
{
	if (this->currentOption > 0) 
	{
		this->text[this->currentOption].setFillColor(sf::Color::White);
		this->currentOption--;
		this->text[currentOption].setFillColor(sf::Color::Red);
		this->changeOption = false;
		this->delayTime = 0.f;
	}
}

void Menu::moveDown()
{
	if (this->currentOption < this->text.size() - 1)
	{
		this->text[this->currentOption].setFillColor(sf::Color::White);
		this->currentOption++;
		this->text[currentOption].setFillColor(sf::Color::Red);
		this->changeOption = false;
		this->delayTime = 0.f;
	}
}

void Menu::update(const float& dt)
{
	if (this->delayTime <= 30.f) 
	{
		this->delayTime += 100 * dt;
	}
	else
	{
		this->changeOption = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->changeOption)
	{
		this->moveUp();
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->changeOption)
	{
		this->moveDown();
	}
}


int Menu::getOption()
{
	return this->currentOption;
}
