/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Faction.hpp"

Faction::Faction(const Prototype *prototype)
	: Object(prototype)
{}

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


int Faction::getFood()
{
	return food;
}


unsigned int Faction::getFactionId()
{
	return factionId;
}


bool Faction::isNeutralFaction(unsigned int uid)
{
	if (!relations.contains(uid))
		qDebug() << "No such faction! " << uid;
	return relations.value(uid) > 0;
}


void Faction::modifyRelation(unsigned int uid, int diff)
{
	if (!relations.contains(uid))
		qDebug() << "No such faction! " << uid;
	relations[uid] += diff;
}
