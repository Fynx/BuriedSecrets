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

	BS::Type getType() const;

	Equipment *getEquipment();
	Journal *getJournal();
	QuestLog *getQuestLog();
	QSet<int> getUnits();
	int getFood();
	int getFactionId();
	bool isNeutralFaction(int uid);
	void modifyRelation(int uid, int diff);

	int consume(int f);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	int food;
	int factionId;
	QHash<int, int> relations;
	Equipment *equipment;
	Journal *journal;
	QuestLog *questLog;
	QSet<int> units;
};
