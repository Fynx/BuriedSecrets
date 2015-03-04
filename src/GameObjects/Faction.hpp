/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Equipment.hpp"
#include "GameObjects/Journal.hpp"
#include "GameObjects/Location.hpp"
#include "GameObjects/QuestLog.hpp"
#include "GameObjects/Unit.hpp"


// Add faction registration in reading function
class Faction : public Object, public Equipped {
public:
	Faction(const Prototype *prototype);

	BS::Type getType() const;

	Journal *getJournal();
	QuestLog *getQuestLog();
	Location *getCamp();

	int getCampUid() const;
	void setCamp(Location *);
	const QSet<int> &getUnitsUids() const;
	const QList<int> &getAllUnitsUids() const;
	bool isAliveMember(int uid) const;
	int getFood() const;
	bool isNeutralFaction(int uid) const;

	void modifyRelation(int uid, int diff);
	int consume(int f);
	void removeUnit(int uid);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	int food;
	QHash<int, int> relations;
	Journal *journal;
	QuestLog *questLog;
	int campUid;
	Location *camp;
	QSet<int> unitsUids;
	QList<int> allUnitsUids;
};
