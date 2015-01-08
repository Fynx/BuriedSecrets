/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/JournalEntry.hpp"

JournalEntry::JournalEntry(const Prototype *prototype)
	: Object(prototype)
{}

QString JournalEntry::getText() const
{
	return prototype->getProperty("text").toString();
}

void JournalEntry::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
}

QJsonObject JournalEntry::saveToJson() const
{
	return Object::saveToJson();
}
