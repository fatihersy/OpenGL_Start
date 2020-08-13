#include "stdafx.h"
#include "HitboxComponent.h"

// CONSTRUCTORS / DESTRUCTORS
HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
	:sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.height = height;
	this->nextPosition.width = width;

	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width,height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}
HitboxComponent::~HitboxComponent()
{

}

// ACCESSORS
const sf::Vector2f & HitboxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}
const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}
const sf::FloatRect& HitboxComponent::getNextPosition(const sf::Vector2f& velosity)
{
	this->nextPosition.left = this->hitbox.getPosition().x + velosity.x;
	this->nextPosition.top = this->hitbox.getPosition().y + velosity.y;

	return this->nextPosition;
}

// MODIFIERS
void HitboxComponent::setPosition(const sf::Vector2f& position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

// FUNCTIONS
bool HitboxComponent::intersects(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}
void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}
void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
