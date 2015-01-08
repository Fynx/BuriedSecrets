/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "GameObjects/Faction.hpp"

Faction::Faction(const Prototype *prototype)
	: Object(prototype)
{}

BS::Type Faction::getType() const
{
	return BS::Type::Faction;
}

Equipment *Faction::getEquipment()
{
	return equipment;
}

Journal *Faction::getJournal()
{
	return journal;
}

QuestLog *Faction::getQuestLog()
{
	return questLog;
}

QSet<int> Faction::getUnits()
{
	return units;
}

int Faction::getFood()
{
	return food;
}

int Faction::getFactionId()
{
	return factionId;
}

bool Faction::isNeutralFaction(int uid)
{
	if (!relations.contains(uid))
		qDebug() << "No such faction! " << uid;
	return relations.value(uid) > 0;
}

void Faction::modifyRelation(int uid, int diff)
{
	if (!relations.contains(uid))
		qDebug() << "No such faction! " << uid;
	relations[uid] += diff;
}

int Faction::consume(int f)
{
	if (food < f){
		int res = f - food;
		food = 0;
		return res;
	}
	food -=f;
	return 0;
}

void Faction::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);

	factionId = json[Properties::Faction].toInt();
	food      = json[Properties::Food].toInt();
}

QJsonObject Faction::saveToJson() const
{
	QJsonObject json = Object::saveToJson();

	json[Properties::Faction] = factionId;
	json[Properties::Food]    = food;

	return json;
}
