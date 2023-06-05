#include "Hitbox.h"

//Constructors / Destructors

Hitbox::Hitbox(sf::Sprite& sprite_, float offsetX_, float offsetY_, float width, float height) :
	sprite(sprite_), offsetX(offsetX_), offsetY(offsetY_)
{
	//initialize hitbox
	this->setPosition(this->sprite.getPosition().x + offsetX,
		this->sprite.getPosition().y + offsetY);
	this->setSize(sf::Vector2f(width, height));
	this->setFillColor(sf::Color::Transparent);
	this->setOutlineColor(sf::Color::Blue);
	this->setOutlineThickness(1.f);
}

Hitbox::~Hitbox()
{
}

//Public functions

void Hitbox::uptade()
{
	//updating hitbox position
	this->setPosition(this->sprite.getPosition().x + this->offsetX,
		this->sprite.getPosition().y + this->offsetY);
}

void Hitbox::render(sf::RenderTarget& target) {
	//draw hitbox
	target.draw(*this);
}
