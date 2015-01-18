/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "Common/Enums.hpp"
#include "GameObjects/Unit.hpp"

using namespace BS;

Unit::Unit(const Prototype *prototype)
	: Object(prototype)
{
	property(Properties::IsSelected) = false;
}

BS::Type Unit::getType() const
{
	return Type::Unit;
}

Item *Unit::getUsedItem()
{
	switch (command){
	case Command::Attack:
		return equipment->getSlotItem(Slot::Weapon);

	case Command::Heal:
		return equipment->getSlotItem(Slot::Medicament);

	case Command::Construct:
	case Command::Deconstruct:
		return equipment->getSlotItem(Slot::Tool);
	default:
		return nullptr;
		break;
	}
}

Location *Unit::getLocation()
{
	return location;
}

void Unit::setLocation(Location *location)
{
	this->location = location;
}

float Unit::getHP() const
{
	return hp;
}

void Unit::setHP(int hp)
{
	this->hp = qMin(hp, getMaxHP());
	this->hp = qMax(this->hp, 0);
}

float Unit::getMaxHP() const
{
	return prototype->getProperty(Properties::HP).toFloat();
}

float Unit::getPsychosis() const
{
	return psychosis;
}

void Unit::setPsychosis(int psychosis)
{
	this->psychosis = qMin(hp, getMaxPsychosis());
	this->psychosis = qMax(this->psychosis, 0);
}

float Unit::getMaxPsychosis() const
{
	return prototype->getProperty(Properties::Psychosis).toFloat();
}

float Unit::getEncumbrance() const
{
	return 0;
	//TODO no equipment;
	return equipment->getWeight();
}

float Unit::getMaxEncumbrance() const
{
	return prototype->getProperty(Properties::Encumbrance).toFloat();
}

float Unit::getFoodDemand() const
{
	//TODO update with things
	return prototype->getProperty(Properties::FoodDemand).toFloat();
}

float Unit::getSightRange() const
{
	//TODO update with things
	return prototype->getProperty(Properties::SightRange).toFloat();
}

float Unit::getSpeed() const
{
	return prototype->getProperty(Properties::MovementSpeed).toFloat();
}

float Unit::getRegeneration() const
{
	return prototype->getProperty(Properties::Regeneration).toFloat();
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

float Unit::getDamageControl() const
{
	float baseValue = prototype->getProperty(Properties::DamageControl).toFloat();
	float additionalValue = (equipment->getSlotItem(BS::Slot::Armor) == nullptr)
		? 0
		: equipment->getSlotItem(BS::Slot::Armor)->getPrototype()->getProperty(Properties::Defense).toFloat();
	return  baseValue + additionalValue;
}

int Unit::getShooting() const
{
	int baseValue = prototype->getProperty(Properties::Shooting).toInt();
	int additionalValue = (equipment->getSlotItem(BS::Slot::Weapon) == nullptr)
		? 0
		: equipment->getSlotItem(BS::Slot::Weapon)->getPrototype()->getProperty(Properties::Attack).toInt();
	return baseValue + additionalValue;
}

int Unit::getEngineering() const
{
	int baseValue = prototype->getProperty(Properties::Engineering).toInt();
	int additionalValue = (equipment->getSlotItem(BS::Slot::Tool) == nullptr)
		? 0
		: equipment->getSlotItem(BS::Slot::Tool)->getPrototype()->getProperty(Properties::Engineering).toInt();
	return baseValue + additionalValue;
}

int Unit::getHealing() const
{
	int baseValue = prototype->getProperty(Properties::Healing).toInt();
	int additionalValue = prototype->getProperty(Properties::Healing).toInt();
	return baseValue + additionalValue;
}

int Unit::getPerception() const
{
	int baseValue = prototype->getProperty(Properties::Perception).toInt();
	int additionalValue = prototype->getProperty(Properties::Perception).toInt();
	return baseValue + additionalValue;
}

/** Action-wise */

QList<QPointF> &Unit::getCurrentPath()
{
	return currentPath;
}

void Unit::setCurrentPath(const QList<QPointF> &path)
{
	currentPath = path;
}

int Unit::getTargetObject() const
{
	return targetObjectUid;
}

void Unit::setTargetObject(int uid)
{
	targetObjectUid = uid;
}

BS::Command Unit::getCommand()
{
	return command;
}

void Unit::setCommand(BS::Command c)
{
	command = c;
}

/** Save & load */

void Unit::loadFromJson(const QJsonObject &json)
{
	//TODO paths blablablah

	Object::loadFromJson(json);

	hp        = json[Properties::HP].toInt();
	psychosis = json[Properties::Psychosis].toInt();
}

QJsonObject Unit::saveToJson() const
{
	QJsonObject json = Object::saveToJson();

	json[Properties::HP]        = hp;
	json[Properties::Psychosis] = psychosis;

	return json;
}
