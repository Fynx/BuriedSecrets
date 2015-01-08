/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Quest.hpp"

Quest::Quest(const Prototype *prototype)
	: Object(prototype)
{}

QString Quest::getDescription() const
{
	return prototype->getProperty("description").toString();
}

void Quest::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
}

QJsonObject Quest::saveToJson() const
{
	return Object::saveToJson();
}
