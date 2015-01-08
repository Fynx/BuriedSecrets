/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Common/Strings.hpp"
#include "GameObjects/Camp.hpp"

Camp::Camp(const Prototype *prototype)
	: Object(prototype)
{}

BS::Type Camp::getType() const
{
	return BS::Type::Camp;
}

qreal Camp::getRange() const
{
	return prototype->getProperty("range").toDouble();
}

void Camp::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
}

QJsonObject Camp::saveToJson() const
{
	return Object::saveToJson();
}
