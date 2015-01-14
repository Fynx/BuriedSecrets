/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "GameObjects/Faction.hpp"

Faction::Faction(const Prototype *prototype)
	: Object(prototype)
{
}

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

const QSet<int> &Faction::getUnits() const
{
	return units;
}

const QList<int> &Faction::getAllUnits() const
{
	return allUnits;
}

int Faction::getFood() const
{
	return food;
}

bool Faction::isNeutralFaction(int uid) const
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

	food = json[Properties::Food].toInt();

	QJsonArray us = json[Properties::Units].toArray();
	for (const QJsonValue &value : us) {
		units.insert(value.toInt());
		allUnits.append(value.toInt());
	}
}

QJsonObject Faction::saveToJson() const
{
	QJsonObject json = Object::saveToJson();

	json[Properties::Food] = food;

	QJsonArray us;
	for (int u : units)
		us.append(u);
	json[Properties::Units] = us;

	return json;
}
