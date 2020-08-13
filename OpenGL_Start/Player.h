#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Entity;

class Player :
	public Entity
{
private:
	//VERIABLES
	bool attacking;

	//INITIALIZER FUNCTIONS
	void initVeriables();
	void initComponents();
public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//FUNCTIONS
	void updateAttack();
	void updateAnimation(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget & target);
};

#endif

