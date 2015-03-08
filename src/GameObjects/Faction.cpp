/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Faction.hpp"

#include "Common/Strings.hpp"
#include "GameObjects/Journal.hpp"
#include "GameObjects/Location.hpp"
#include "GameObjects/QuestLog.hpp"
#include "GameObjects/Unit.hpp"

Faction::Faction(const Prototype *prototype)
	: Object(prototype)
{
}

BS::Type Faction::getType() const
{
	return BS::Type::Faction;
}

Journal *Faction::getJournal()
{
	return journal;
}

QuestLog *Faction::getQuestLog()
{
	return questLog;
}

Location *Faction::getCamp()
{
	return camp;
}

void Faction::setCamp(Location *c)
{
	camp = c;
	campUid = c->getUid();
}

int Faction::getCampUid() const
{
	return campUid;
}

const QSet<int> &Faction::getUnitsUids() const
{
	return unitsUids;
}

const QList<int> &Faction::getAllUnitsUids() const
{
	return allUnitsUids;
}

bool Faction::isAliveMember(int uid) const
{
	return unitsUids.contains(uid);
}

int Faction::getFood() const
{
	return food;
}

bool Faction::isNeutralFaction(int uid) const
{
	if (uid == 0)
		return true;
	if (!relations.contains(uid))
		qDebug() << "No such faction! " << uid;
	return relations.value(uid) > 0;
}

bool Faction::isFriendly(Object* obj)
{
	return isNeutralFaction(obj->getFactionId()) || obj->getFactionId() == getFactionId();
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
	food -= f;
	return 0;
}

void Faction::removeUnit(int uid)
{
	unitsUids.remove(uid);
}

void Faction::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
	Equipped::loadFromJson(json);

	food = json[Attributes::Food].toInt();
	campUid = json[Attributes::CampId].toInt();

	QJsonArray us = json[Attributes::Units].toArray();
	for (const QJsonValue &value : us) {
		unitsUids.insert(value.toInt());
		allUnitsUids.append(value.toInt());
	}
	QJsonArray rels = json[Attributes::Relations].toArray();
	for (const QJsonValue &value : rels) {
		relations[value.toArray().first().toInt()] = value.toArray().last().toInt();
	}
}

QJsonObject Faction::saveToJson() const
{
	QJsonObject json = Object::saveToJson();
	for (const QString &key : Equipped::saveToJson().keys())
		json[key] = Equipped::saveToJson()[key];

	json[Attributes::Food] = food;
	json[Attributes::CampId] = campUid;

	QJsonArray us;
	for (int u : unitsUids)
		us.append(u);
	json[Attributes::Units] = us;

	return json;
}
