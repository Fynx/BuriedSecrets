/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "Common/Enums.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include <QtGlobal>

using namespace BS;

Unit::Unit(const Prototype *prototype)
	: Object(prototype), frags(0)
{
	location = nullptr;
	attitude = Attitude::Guard;
	command = Command::None;
	setPsychosis(0);
	setNearestEnemy(nullptr);
	setTargetAngle(-1);
}

Unit::~Unit()
{
}

BS::Type Unit::getType() const
{
	return Type::Unit;
}

Item *Unit::getUsedItem() const
{
	switch (command) {
	case Command::Attack:
		return getEquipment()->getSlotItem(Slot::Weapon);

	case Command::Heal:
		return getEquipment()->getSlotItem(Slot::Medicament);

	case Command::Assemble:
		return getEquipment()->getSlotItem(Slot::Fortification);

	case Command::Disassemble:
		return getEquipment()->getSlotItem(Slot::Tool);
	default:
		return nullptr;
		break;
	}
}

Location *Unit::getLocation() const
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
	this->hp = qMin(float(hp), getMaxHP());
	this->hp = qMax(this->hp, 0);
	if (this->hp == 0)
		info(getName() + " should be dead...");
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
	this->psychosis = qMin(float(psychosis), getMaxPsychosis());
	this->psychosis = qMax(this->psychosis, 0);
}

float Unit::getMaxPsychosis() const
{
	return prototype->getProperty(Properties::Psychosis).toFloat();
}

float Unit::getEncumbrance() const
{
	return getEquipment()->getWeight();
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
	float result = float(getPerception()) * prototype->getProperty(Properties::SightRange).toFloat();
	if (getLocation() && attitude == Attitude::BuildingAggressive)
		result += getLocation()->getPrototype()->getProperty(Properties::BigRangeBonus).toFloat();

	return result;
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
	return getEquipment()->addItem(item);
}

void Unit::removeItem(Item *item)
{
	return getEquipment()->removeItem(item);
}

/** Skills
 *
 * Feel free to modify the names.
 */

float Unit::getDamageControl() const
{
	float baseValue = prototype->getProperty(Properties::DamageControl).toFloat();
	float additionalValue = (getEquipment()->getSlotItem(Slot::Armor) == nullptr)
			? 0
			: getEquipment()->getSlotItem(Slot::Armor)->getPrototype()->getProperty(Properties::Defense).toFloat();

	if (getLocation() && attitude == Attitude::BuildingDefensive)
		additionalValue += getLocation()->getPrototype()->getProperty(Properties::BigDefBonus).toFloat();
	if (getLocation() && attitude == Attitude::BuildingAggressive)
		additionalValue += getLocation()->getPrototype()->getProperty(Properties::SmallDefBonus).toFloat();
	return qMin(baseValue + additionalValue, 1.0f);
}

int Unit::getAttack() const
{
	int baseValue = prototype->getProperty(Properties::Attack).toInt();
	int additionalValue = (getEquipment()->getSlotItem(BS::Slot::Weapon) == nullptr)
		? 0
		: getEquipment()->getSlotItem(Slot::Weapon)->getPrototype()->getProperty(Properties::Dispersion).toInt();

	if (getLocation() && attitude == Attitude::BuildingAggressive)
		additionalValue += getLocation()->getPrototype()->getProperty(Properties::BigAttBonus).toInt();
	return qMax(0, baseValue + additionalValue);
}

int Unit::getEngineering() const
{
	int baseValue = prototype->getProperty(Properties::Engineering).toInt();
	int additionalValue = (getEquipment()->getSlotItem(BS::Slot::Tool) == nullptr)
		? 0
		: getEquipment()->getSlotItem(BS::Slot::Tool)->getPrototype()->getProperty(Properties::Engineering).toInt();
	return baseValue + additionalValue;
}

int Unit::getHealing() const
{
	int baseValue = prototype->getProperty(Properties::Healing).toInt();
	int additionalValue = (getEquipment()->getSlotItem(Slot::Medicament) == nullptr)
		? 0
		: getEquipment()->getSlotItem(Slot::Medicament)->getPrototype()->getProperty(Properties::Healing).toInt();
	return baseValue + additionalValue;
}

int Unit::getPerception() const
{
	int baseValue = prototype->getProperty(Properties::Perception).toInt();
	int additionalValue = (getEquipment()->getSlotItem(Slot::Perception) == nullptr)
		? 0
		: getEquipment()->getSlotItem(Slot::Perception)->getPrototype()->getProperty(Properties::Perception).toInt();

	return baseValue + additionalValue;
}

/** Action-wise */

QList<QPointF> &Unit::getCurrentPath()
{
	return currentPath;
}

const QList<QPointF> Unit::getCurrentPath() const
{
	return currentPath;
}

void Unit::setCurrentPath(const QList<QPointF> &path)
{
	currentPath = path;
}

QVector<QPointF> Unit::getPatrolRoute() const
{
	return patrolRoute;
}

void Unit::setPatrolRoute(const QVector< QPointF > &route)
{
	patrolRoute = route;
}

int Unit::getTargetObject() const
{
	return targetObjectUid;
}

void Unit::setTargetObject(int uid)
{
	targetObjectUid = uid;
}

QPointF Unit::getTargetPoint()
{
	return targetPoint;
}

void Unit::setTargetPoint(QPointF p)
{
	targetPoint = p;
}

float Unit::getTargetAngle()
{
	return targetAngle;
}

void Unit::setTargetAngle(float angle)
{
	targetAngle = angle;
}

BS::Attitude Unit::getAttitude() const
{
	return attitude;
}

void Unit::setAttitude(Attitude a)
{
	attitude = a;
}

BS::Command Unit::getCommand()
{
	return command;
}

void Unit::setCommand(BS::Command c)
{
	if ((getState() == State::RunBase || getState() == State::IdleBase) && (c != Command::Assemble && c != Command::Move && c != Command::Base))
		return;
	command = c;
}

const Object *Unit::getNearestEnemy() const
{
	return nearestEnemy;
}

void Unit::setNearestEnemy(const Object *obj)
{
	nearestEnemy = obj;
}

int Unit::getFrags() const
{
	return frags;
}

void Unit::incFrags()
{
	++frags;
}

/** Save & load */

void Unit::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
	Equipped::loadFromJson(json);

	hp           = json[Attributes::HP].toInt();
	psychosis    = json[Attributes::Psychosis].toInt();

	command  = static_cast<BS::Command>(json[Attributes::Command].toInt());

	if (json.contains(Attributes::PatrolRoute)) {
		for (const QJsonValue &val : json[Attributes::PatrolRoute].toArray()) {
			if (!val.isArray() || val.toArray().size() != 2) {
				err("Invalid route");
				return;
			}
			patrolRoute.append(QPointF(val.toArray()[0].toDouble(), val.toArray()[1].toDouble()));
		}
	}

	QJsonArray tpa = json[Attributes::TargetPoint].toArray();
	targetPoint = {tpa.first().toDouble(), tpa.last().toDouble()};

	if (targetPoint.x() != 0)
		qDebug() << "targetPoint:" << targetPoint;

	frags = json[Attributes::Frags].toInt();

	qDebug() << "loaded frags:" << frags;
}

QJsonObject Unit::saveToJson() const
{
	QJsonObject json = Object::saveToJson();

	if (!getEquipment()->isEmpty())
		for (const QString &key : Equipped::saveToJson().keys())
			json[key] = Equipped::saveToJson()[key];

	json[Attributes::HP]        = hp;
	json[Attributes::Psychosis] = psychosis;

	json[Attributes::Command] = static_cast<int>(command);

	QJsonArray jPatrolRoute;
	for (const QPointF &point : patrolRoute) {
		QJsonArray jPoint({point.x(), point.y()});
		jPatrolRoute.append(jPoint);
	}
	if (!jPatrolRoute.isEmpty())
		json[Attributes::PatrolRoute] = jPatrolRoute;

	QJsonArray tpa = {targetPoint.x(), targetPoint.y()};
	json[Attributes::TargetPoint] = tpa;

	json[Attributes::Frags] = frags;

	return json;
}
