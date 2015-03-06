/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Common/Strings.hpp"
#include "GameObjects/Environment.hpp"

Environment::Environment(const Prototype *prototype)
	: Object(prototype)
{}

BS::Type Environment::getType() const
{
	return BS::Type::Environment;
}

bool Environment::isObstacle() const
{
	return getPrototype()->getProperty(Properties::Obstacle).toBool();
}

bool Environment::isTransparent() const
{
	return getPrototype()->getProperty(Properties::Transparent).toBool();
}

void Environment::loadFromJson(const QJsonObject &json)
{
	return Object::loadFromJson(json);
}

QJsonObject Environment::saveToJson() const
{
	return Object::saveToJson();
}
