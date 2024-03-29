/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Journal.hpp"
#include "GameObjects/Faction.hpp"
#include "GameObjects/Location.hpp"
#include "GameObjects/Unit.hpp"

Faction::Faction(const Prototype *prototype)
	: Object(prototype), journalUid(Object::InvalidUid), journal(nullptr), totalFrags(0)
{}

BS::Type Faction::getType() const
{
	return BS::Type::Faction;
}

int Faction::getJournalUid() const
{
	return journalUid;
}

void Faction::setJournal(Journal *newJournal)
{
	if (newJournal == nullptr)
		warn("Setting nullptr Journal.");
	journal = newJournal;
}

Journal *Faction::getJournal()
{
	if (journal == nullptr)
		warn("Returning nullptr Journal.");
	return journal;
}

void Faction::setCamp(int c)
{
	campUid = c;
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

QList<int> Faction::getPendingUnitsUids() const
{
	return pendingUids.toList();
}

void Faction::addPendingUnit(int uid)
{
	pendingUids.insert(uid);
}

void Faction::removePendingUnit(int uid)
{
	pendingUids.remove(uid);
}

bool Faction::isAliveMember(int uid) const
{
	return unitsUids.contains(uid);
}

int Faction::getFood() const
{
	return food;
}

double Faction::getCampRange() const
{
	return campRange;
}

bool Faction::isNeutralFaction(int uid) const
{
	if (uid == 0)
		return true;
// 	if (!relations.contains(uid))
// 		qDebug() << "No such faction! " << uid;
	return relations.value(uid) > 0;
}

bool Faction::isFriendly(const Object *obj)
{
	return isNeutralFaction(obj->getFactionId()) || obj->getFactionId() == getFactionId();
}

void Faction::modifyRelation(int uid, int diff)
{
// 	if (!relations.contains(uid))
// 		qDebug() << "No such faction! " << uid;
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

void Faction::addUnit(int uid)
{
	unitsUids.insert(uid);
	allUnitsUids.append(uid);
}

QList<int> Faction::getQuests() const
{
	return quests;
}

int Faction::getTotalFrags() const
{
	return totalFrags;
}

void Faction::incTotalFrags()
{
	++totalFrags;
}

void Faction::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
	Equipped::loadFromJson(json);

	food = json[Attributes::Food].toInt();
	campUid = json[Attributes::CampId].toInt();
	campRange = json[Attributes::CampRange].toDouble();

	QJsonArray us = json[Attributes::Units].toArray();
	for (const QJsonValue &value : us) {
		unitsUids.insert(value.toInt());
		allUnitsUids.append(value.toInt());
	}

	QJsonArray rels = json[Attributes::Relations].toArray();
	for (const QJsonValue &value : rels)
		relations[value.toArray().first().toInt()] = value.toArray().last().toInt();

	journalUid = json[Attributes::Journal].toInt();

	for (const QJsonValue &value : json[Attributes::Quests].toArray())
		quests.append(value.toInt());

	totalFrags = json[Attributes::Frags].toInt();
}

QJsonObject Faction::saveToJson() const
{
	QJsonObject json = Object::saveToJson();
	for (const QString &key : Equipped::saveToJson().keys())
		json[key] = Equipped::saveToJson()[key];

	json[Attributes::Food] = food;
	json[Attributes::CampId] = campUid;
	if (campRange != 0)
		json[Attributes::CampRange] = campRange;

	QJsonArray us;
	for (int u : unitsUids)
		us.append(u);
	json[Attributes::Units] = us;

	QJsonArray rels;
	for (int key : relations.keys())
		rels.append(QJsonArray({key, relations[key]}));
	json[Attributes::Relations] = rels;

	if (journal != nullptr)
		json[Attributes::Journal] = journal->getUid();

	QJsonArray qus;
	for (int quest : quests)
		qus.append(quest);
	json[Attributes::Quests] = qus;

	json[Attributes::Frags] = totalFrags;

	return json;
}
