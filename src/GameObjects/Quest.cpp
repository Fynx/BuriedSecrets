/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Quest.hpp"

Quest::Quest(const Prototype *prototype)
	: Object(prototype),
	  startEntry(0),
	  failEntry(0),
	  successEntry(0)
{}

void Quest::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
}

QJsonObject Quest::saveToJson() const
{
	return Object::saveToJson();
}
