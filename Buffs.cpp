#include "Buffs.h"

//Initialize functions

void Buffs::initSprites(const std::vector<int>& drawnBuffs)
{
	//Initiliaze texture and sprites
	this->texture = std::make_unique<sf::Texture>();
	this->texture->loadFromFile("./Textures/buffs.png");
	this->sprites = std::vector<std::pair<sf::Sprite, int >>(3);
	
	//setting position of sprites, and textures
	float x{ 200 }, y{ 350 };
	for (size_t i = 0; i < 3; i++)
	{
		this->sprites[i].first.setTexture(*this->texture);
		this->sprites[i].first.setTextureRect(sf::IntRect(16 * drawnBuffs[i], 0, 16, 16));
		this->sprites[i].first.setScale(10.f, 10.f);
		this->sprites[i].first.setPosition(x, y);
		this->sprites[i].second = drawnBuffs[i];
		x += 200.f;
	}
	this->sprites[0].first.setScale(12.f, 12.f);
}

void Buffs::initVariables()
{
	//init options
	this->delayTime = 0.f;
	this->changeOption = true;
	this->currentOption = 0;
}

//Constructors / Destructors

Buffs::Buffs(const std::vector<int>& drawnBuffs)
{
	//init variables
	this->initVariables();
	this->initSprites(drawnBuffs);
}

Buffs::~Buffs()
{
}

//Public functions

void Buffs::moveRight()
{
	//setting current option to right one
	if (this->currentOption < 2)
	{
		//make default scale of prievous option
		this->sprites[this->currentOption].first.setScale(10.f, 10.f);
		//setting current option
		this->currentOption++;
		this->sprites[currentOption].first.setScale(12.f, 12.f);
		//reseting delay of changing option
		this->changeOption = false;
		this->delayTime = 0.f;
	}
}

void Buffs::moveLeft()
{
	//setting current option to left one 
	if (this->currentOption > 0)
	{
		//make dafault scale of prievous option 
		this->sprites[this->currentOption].first.setScale(10.f, 10.f);
		//setting current option
		this->currentOption--;
		this->sprites[currentOption].first.setScale(12.f, 12.f);
		//reseting delay of changing option
		this->changeOption = false;
		this->delayTime = 0.f;
	}
}

int Buffs::getOption() const
{
	//getting of chosen buff 
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->changeOption)
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
