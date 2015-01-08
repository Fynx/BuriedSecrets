/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Mob.hpp"

Mob::Mob(const Prototype *prototype)
	: Object(prototype)
{}

BS::Type Mob::getType() const
{
	return BS::Type::Mob;
}

void Mob::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
}

QJsonObject Mob::saveToJson() const
{
	return Object::saveToJson();
}
