/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Unit.hpp"

Unit::Unit(const Prototype *prototype)
	: Object(prototype)
{}

BS::Type Unit::getType() const
{
	return BS::Type::Unit;
}

Location *Unit::getLocation()
{
	return location;
}

void Unit::setLocation(Location *location)
{
	this->location = location;
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

/** Skills
 *
 * Feel free to modify the names.
 */

int Unit::getDamageControl() const
{
	int baseValue = prototype->getProperty("damageControl").toInt();
	int additionalValue = (armor == nullptr)
		? 0
		: armor->getPrototype()->getProperty("defense").toInt();
	return  baseValue + additionalValue;
}

int Unit::getShooting() const
{
	int baseValue = prototype->getProperty("shooting").toInt();
	int additionalValue = (weapon == nullptr)
		? 0
		: armor->getPrototype()->getProperty("attack").toInt();
	return baseValue + additionalValue;
}

int Unit::getEngineering() const
{
	int baseValue = prototype->getProperty("engineering").toInt();
	int additionalValue = (tools == nullptr)
		? 0
		: tools->getPrototype()->getProperty("engineering").toInt();
	return baseValue + additionalValue;
}

int Unit::getHealing() const
{
	int baseValue = prototype->getProperty("healing").toInt();
	int additionalValue = prototype->getProperty("healing").toInt();
	return baseValue + additionalValue;
}

int Unit::getPerception() const
{
	int baseValue = prototype->getProperty("perception").toInt();
	int additionalValue = prototype->getProperty("perception").toInt();
	return baseValue + additionalValue;
}

/** Action-wise */

QList<QPointF> Unit::getCurrentPath() const
{
	return currentPath;
}

void Unit::setCurrentPath(const QList<QPointF> &path)
{
	currentPath = path;
}

int Unit::getAttackedUnitUid() const
{
	return attackedUnitUid;
}

void Unit::setAttackedUnitUid(int uid)
{
	attackedUnitUid = uid;
}
