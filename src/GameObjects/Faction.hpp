/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"
#include "GameObjects/Equipment.hpp"

class Journal;
class Location;
class QuestLog;
class Unit;

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
	bool isFriendly(Object *obj);

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
