#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H

class AttributeComponent 
{

public:
	// LEVELING
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned attributePoints;

	// ATTRIBUTES
	unsigned vitality;
	unsigned strength;
	unsigned dexterity;
	unsigned agility;
	unsigned intelligence;

	// STATS
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;

	// CONSTRUCTOR / DESTRUCTOR
	AttributeComponent(unsigned level);
	virtual ~AttributeComponent();

	// FUNCTIONS
};

#endif

