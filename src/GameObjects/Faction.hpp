/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Equipment.hpp"
#include "GameObjects/Journal.hpp"
#include "GameObjects/QuestLog.hpp"
#include "GameObjects/Unit.hpp"

class Faction : public Object {
public:
	Faction(const Prototype *prototype);

	Equipment *getEquipment();
	Journal *getJournal();
	QuestLog *getQuestLog();
	QSet<int> getUnits();

	int consume(int f);

private:
	int food;
	Equipment *equipment;
	Journal *journal;
	QuestLog *questLog;
	QSet<int> units;
};
