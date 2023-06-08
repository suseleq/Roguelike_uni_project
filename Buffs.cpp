#include "Buffs.h"

//Initialize functions

void Buffs::initSprites(const std::vector<int>& drawnBuffs)
{
	//Initiliaze texture and sprites
	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/buffs.png");
	this->sprites = std::vector<std::pair<sf::Sprite, int >>(3);
	
	//setting position of sprites, and icon of buff
	float x{ 300 }, y{ 300 };
	for (size_t i = 0; i < 3; i++)
	{
		this->sprites[i].first.setTexture(*this->texture);
		this->sprites[i].first.setTextureRect(sf::IntRect(32 * drawnBuffs[i], 0, 32, 32));
		this->sprites[i].first.setScale(2.f, 2.f);
		this->sprites[i].first.setPosition(x, y);
		this->sprites[i].second = drawnBuffs[i];
		y += 150.f;
	}
	this->sprites[0].first.setScale(3.f, 3.f);
}

void Buffs::initVariables()
{
	this->delayTime = 0.f;
	this->changeOption = true;
	this->currentOption = 0;
}

//Constructors / Destructors

Buffs::Buffs(const std::vector<int>& drawnBuffs)
{
	this->initVariables();
	this->initSprites(drawnBuffs);
}

Buffs::~Buffs()
{
}

//Public functions

void Buffs::moveRight()
{
	//setting the right option
	if (this->currentOption > 0)
	{
		this->sprites[this->currentOption].first.setScale(2.f, 2.f);
		this->currentOption--;
		this->sprites[currentOption].first.setScale(3.f, 3.f);
		this->changeOption = false;
		this->delayTime = 0.f;
	}
}

void Buffs::moveLeft()
{
	//setting the bottom option
	if (this->currentOption < 2)
	{
		this->sprites[this->currentOption].first.setScale(2.f, 2.f);
		this->currentOption++;
		this->sprites[currentOption].first.setScale(3.f, 3.f);
		this->changeOption = false;
		this->delayTime = 0.f;
	}
}

int Buffs::getOption() const
{
	return this->sprites[this->currentOption].second;
}

void Buffs::update(const float& dt)
{
	//Updating delay time
	if (this->delayTime <= 30.f)
	{
		this->delayTime += 100 * dt;
	}
	else
	{
		this->changeOption = true;
	}

	//Update current option
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->changeOption)
	{
		this->moveRight();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->changeOption)
	{
		this->moveLeft();

	}

}

void Buffs::render(sf::RenderTarget& target)
{
	//Render sprites
	for (auto& i : this->sprites)
	{
		target.draw(i.first);
	}
}
