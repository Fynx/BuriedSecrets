/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "GameObjects/QuestLog.hpp"

QuestLog::QuestLog(const Prototype *prototype)
	: Object(prototype)
{}

void QuestLog::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
}

QJsonObject QuestLog::saveToJson() const
{
	return Object::saveToJson();
}
