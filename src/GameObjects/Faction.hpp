/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Equipment.hpp"
#include "GameObjects/Journal.hpp"
#include "GameObjects/QuestLog.hpp"
#include "GameObjects/Unit.hpp"
#include "GameObjects/Camp.hpp"


// Add faction registration in reading function
class Faction : public Object {
public:
	Faction(const Prototype *prototype);

	BS::Type getType() const;

	Equipment *getEquipment();
	Journal *getJournal();
	QuestLog *getQuestLog();
	Camp *getCamp();

	const QSet<int> &getUnits() const;
	const QList<int> &getAllUnits() const;
	bool isAliveMember(int uid) const;
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
	Camp *camp;
	QSet<int> units;
	QList<int> allUnits;
};
