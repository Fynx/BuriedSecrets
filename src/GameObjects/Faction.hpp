/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Equipment.hpp"
#include "GameObjects/Journal.hpp"
#include "GameObjects/QuestLog.hpp"
#include "GameObjects/Unit.hpp"


// Add faction registration in reading function
class Faction : public Object {
public:
	Faction(const Prototype *prototype);

	Equipment *getEquipment();
	Journal *getJournal();
	QuestLog *getQuestLog();
	QSet<int> getUnits();
	int getFood();
	unsigned int getFactionId();
	bool isNeutralFaction(unsigned int uid);
	void modifyRelation(unsigned int uid, int diff);

	int consume(int f);

private:
	int food;
	unsigned int factionId;
	QHash<unsigned int, int> relations;
	Equipment *equipment;
	Journal *journal;
	QuestLog *questLog;
	QSet<int> units;
};
