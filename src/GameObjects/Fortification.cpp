/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Fortification.hpp"

Fortification::Fortification(const Prototype *prototype)
	: Object(prototype)
{}

BS::Type Fortification::getType() const
{
	return BS::Type::Fortification;
}

void Fortification::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
}

QJsonObject Fortification::saveToJson() const
{
	return Object::saveToJson();
}
