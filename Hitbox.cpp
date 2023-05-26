#include "Hitbox.h"

Hitbox::Hitbox(sf::Sprite& sprite_, float offsetX_, float offsetY_, float width, float height) :
	sprite(sprite_), offsetX(offsetX_), offsetY(offsetY_)
{
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


void Hitbox::uptade()
{
	this->setPosition(this->sprite.getPosition().x + this->offsetX,
		this->sprite.getPosition().y + this->offsetY);
}

void Hitbox::render(sf::RenderTarget& target) {
	target.draw(*this);
}
