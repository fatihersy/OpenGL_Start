#include "stdafx.h"
#include "Entity.h"

// INITS
void Entity::initVariables()
{
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
}

// CONSTRUCTOR / DESTRUCTOR
Entity::Entity()
{
	this->initVariables();
}
Entity::~Entity()
{
	delete this->animationComponent;
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->attributeComponent;
}

// COMPONENT FUNCTIONS
void Entity::setTexture(sf::Texture & texture)
{
	this->sprite.setTexture(texture);
}
void Entity::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}
void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}
void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createAttributeComponent()
{
	this->attributeComponent = new AttributeComponent();
}

// ACCESSORS
const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent) return this->hitboxComponent->getPosition();

	return this->sprite.getPosition();
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
	if (this->hitboxComponent) 
	return sf::Vector2i(
			static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI,
			static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI
			);
		
	return 	sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeI
		);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent) return this->hitboxComponent->getGlobalBounds();
	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
	if (this->hitboxComponent && this->movementComponent)
		return
		this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
		
	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

// MODIFIERS
void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent) return this->hitboxComponent->setPosition(sf::Vector2f(x, y));

	return this->sprite.setPosition(x, y);
}

// FUNCTIONS
void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent) 
	{
		this->movementComponent->move(dir_x,dir_y, dt);// SETS VELOCITY
	}
}
void Entity::stopVelocity()
{
	if(this->movementComponent) this->movementComponent->stopVelocity();
}
void Entity::stopVelocityX()
{
	if (this->movementComponent) this->movementComponent->stopVelocityX();
}
void Entity::stopVelocityY()
{
	if (this->movementComponent) this->movementComponent->stopVelocityY();
}
void Entity::update(const float& dt)
{
	
}
void Entity::render(sf::RenderTarget& target){}
