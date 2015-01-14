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

	const QSet<int> &getUnits() const;
	int getFood() const;
	bool isNeutralFaction(int uid) const;

	void modifyRelation(int uid, int diff);
	int consume(int f);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	int food;
	QHash<int, int> relations;
	Equipment *equipment;
	Journal *journal;
	QuestLog *questLog;
	QSet<int> units;
};
