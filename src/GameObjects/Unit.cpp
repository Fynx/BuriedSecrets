/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Unit.hpp"

Unit::Unit(const Prototype *prototype)
	: Object(prototype)
{}

Object::Type Unit::getType() const
{
	return Object::Type::Unit;
}

int Unit::getHP() const
{
	return hp;
}

void Unit::setHP(int hp)
{
	this->hp = hp;
}

int Unit::getMaxHP() const
{
	return prototype->getProperty("hp").toInt();
}

int Unit::getPsychosis() const
{
	return psychosis;
}

void Unit::setPsychosis(int psychosis)
{
	this->psychosis = psychosis;
}

int Unit::getMaxPsychosis() const
{
	return prototype->getProperty("psychosis").toInt();
}

int Unit::getEncumbrance() const
{
	return equipment->getWeight();
}

int Unit::getMaxEncumbrance() const
{
	return prototype->getProperty("encumbrance").toInt();
}

int Unit::getFoodDemand() const
{
	//TODO update with things
	return prototype->getProperty("foodDemand").toInt();
}

int Unit::getSightRange() const
{
	//TODO update with things
	return prototype->getProperty("sightRange").toInt();
}

void Unit::addItem(Item *item)
{
	return equipment->addItem(item);
}

void Unit::removeItem(Item *item)
{
	return equipment->removeItem(item);
}
