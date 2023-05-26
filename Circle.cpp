#include "Circle.h"

Circle::Circle(sf::Sprite& sprite_, float offsetX_, float offsetY_, int radius) : sprite(sprite_), offsetX(offsetX_), offsetY(offsetY_)
{
	this->setRadius(radius);
	this->setPosition(sprite.getPosition().x - this->getRadius() / 2 + offsetX / 2,
		sprite.getPosition().y - this->getRadius() / 2 + offsetY / 2);
}

Circle::~Circle()
{
}

void Circle::uptade()
{
	this->setPosition(sprite.getPosition().x - this->getGlobalBounds().height / 2 + offsetX / 2,
		sprite.getPosition().y - this->getGlobalBounds().height / 2 + offsetY / 2);
}

void Circle::render(sf::RenderTarget& target)
{
	target.draw(*this);
}
