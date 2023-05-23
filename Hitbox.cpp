#include "Hitbox.h"

Hitbox::Hitbox(sf::Sprite& sprite_, float offsetX_, float offsetY_, float width, float height) :
	sprite(sprite_), offsetX(offsetX_), offsetY(offsetY_)
{
	this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.width = width;
	this->nextPosition.height = height;

	this->hitboxShape.setPosition(this->sprite.getPosition().x + offsetX,
		this->sprite.getPosition().y + offsetY);
	this->hitboxShape.setSize(sf::Vector2f(width, height));
	this->hitboxShape.setFillColor(sf::Color::Transparent);
	this->hitboxShape.setOutlineColor(sf::Color::Green);
	this->hitboxShape.setOutlineThickness(1.f);
}

Hitbox::~Hitbox()
{
}

const sf::Vector2f& Hitbox::getPosition() const
{
	return this->hitboxShape.getPosition();
}

const sf::FloatRect Hitbox::getGlobalBound() const
{
	return this->hitboxShape.getGlobalBounds();
}

const sf::FloatRect& Hitbox::getNextPosition(const sf::Vector2f& velocity)
{
	this->nextPosition.left = this->hitboxShape.getPosition().x + velocity.x;
	this->nextPosition.top = this->hitboxShape.getPosition().y + velocity.y;
	return this->nextPosition;
}

void Hitbox::setPosition(const sf::Vector2f& position)
{
	this->hitboxShape.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

bool Hitbox::intersects(const sf::FloatRect& rect)
{
	return this->hitboxShape.getGlobalBounds().intersects(rect);
}

void Hitbox::uptade()
{
	this->hitboxShape.setPosition(this->sprite.getPosition().x + this->offsetX,
		this->sprite.getPosition().y + this->offsetY);
}

void Hitbox::render(sf::RenderTarget& target) {
	target.draw(this->hitboxShape);
}
