#include "stdafx.h"
#include "MovementComponent.h"

// CONSTRUCTOR / DESTRUCTOR
MovementComponent::MovementComponent(sf::Sprite& sprite, 
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}
MovementComponent::~MovementComponent()
{

}

 // ACCESSORS
const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}
const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

// FUNCTIONS
/*
const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (velocity.x == 0.f && velocity.y == 0.f) {
			return true;
			break;
		}
	case MOVING_LEFT:
		if (velocity.x < 0.f) {
			return true;
			break;
		}
	case MOVING_RIGHT:
		if (velocity.x > 0.f) {
			return true;
			break;
		}
	case MOVING_UP:
		if (velocity.y > 0.f) {
			return true;
			break;
		}
	case MOVING_DOWN:
		if (velocity.y < 0.f) {
			return true;
			break;
		}
	}

	return false;
}
*/

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f) return true;
		break;
	case MOVING_LEFT:
		if (this->velocity.x < 0.f) return true;
		break;
	case MOVING_RIGHT:
		if (this->velocity.x > 0.f) return true;
		break;
	case MOVING_UP:
		if (this->velocity.y > 0.f) return true;
		break;
	case MOVING_DOWN:
		if (this->velocity.y < 0.f) return true;
		break;
	case MOVING:
		if (this->velocity.y < 0.f) return true;
		break;
	default:
		return false;
		break;
	}

	return false;
}

void MovementComponent::stopVelocity()
{
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	this->velocity.y = 0.f;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	// Acceleration a sprite until it reaches the max velocity

	this->velocity.x += this->acceleration * dir_x * dt;
	this->velocity.y += this->acceleration * dir_y * dt;
}
void MovementComponent::update(const float& dt)
{
	/*  

	DECELERATION THE SPRITE AND CONTROLS THE MAXIMUM VELOCITY.
	MOVES TO SPRITE

	*/
	if (this->velocity.x > 0.f) // Check for Positive x
	{
		// MAX VELOCITY CHECK X POSITIVE
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		// DECELERATION X POSITIVE
		this->velocity.x -= deceleration * dt;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;

	}
	else if (this->velocity.x < 0.f) // Check for Negative x
	{
		// MAX VELOCITY CHECK X NEGATIVE
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		// DECELERATION X NEGATIVE
		this->velocity.x += deceleration * dt;
		if (this->velocity.x > 0.f )
			this->velocity.x = 0.f;
	}


	if (this->velocity.y > 0.f) // Check for Positive y
	{
		// MAX VELOCITY CHECK Y POSITIVE
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		// DECELERATION Y POSITIVE
		this->velocity.y -= deceleration * dt;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;

	}
	else if (this->velocity.y < 0.f) // Check for Negative y
	{
		// MAX VELOCITY CHECK Y NEGATIVE
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		// DECELERATION Y NEGATIVE
		this->velocity.y += deceleration * dt;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	// FINAL MOVE
	this->sprite.move(this->velocity * dt); // USES VELOCITY
}
