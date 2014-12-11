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

QSet<Unit *> Faction::getUnits()
{
	return units;
}
