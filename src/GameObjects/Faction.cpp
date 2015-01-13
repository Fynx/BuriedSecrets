/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "GameObjects/Faction.hpp"

Faction::Faction(const Prototype *prototype)
	: Object(prototype)
{
	factionId = prototype->getProperty(Properties::Faction).toInt();
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

int Faction::getFood() const
{
	return food;
}

int Faction::getFactionId() const
{
	return factionId;
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
}

QJsonObject Faction::saveToJson() const
{
	QJsonObject json = Object::saveToJson();

	json[Properties::Food] = food;

	return json;
}
