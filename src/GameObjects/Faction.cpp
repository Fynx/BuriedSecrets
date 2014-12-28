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
