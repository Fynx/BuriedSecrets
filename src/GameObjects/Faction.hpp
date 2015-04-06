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

//TODO Add faction registration in reading function
class Faction : public Object, public Equipped {
public:
	Faction(const Prototype *prototype);

	BS::Type getType() const;

	int getJournalUid() const;
	void setJournal(Journal *journal);

	Journal *getJournal();
	QuestLog *getQuestLog();

	int getCampUid() const;
	void setCamp(int);
	const QSet<int> &getUnitsUids() const;
	const QList<int> &getAllUnitsUids() const;
	bool isAliveMember(int uid) const;
	int getFood() const;
	double getCampRange() const;
	bool isNeutralFaction(int uid) const;
	bool isFriendly(const Object *obj);

	void modifyRelation(int uid, int diff);
	int consume(int f);
	void removeUnit(int uid);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	int food;
	QHash<int, int> relations;

	int journalUid;
	Journal *journal;
	QuestLog *questLog;

	int campUid;
	double campRange;

	QSet<int> unitsUids;
	QList<int> allUnitsUids;
};
