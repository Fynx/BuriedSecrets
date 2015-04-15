/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"
#include "GameObjects/Equipment.hpp"

class Journal;
class Location;
class Unit;


class Faction : public Object, public Equipped {
public:
	Faction(const Prototype *prototype);

	BS::Type getType() const;

	int getJournalUid() const;
	void setJournal(Journal *journal);

	Journal *getJournal();

	int getCampUid() const;
	void setCamp(int);

	void removeUnit(int uid);
	void addUnit(int uid);
	const QSet<int> &getUnitsUids() const;
	const QList<int> &getAllUnitsUids() const;
	QList<int> getPendingUnitsUids() const;
	void addPendingUnit(int uid);
	void removePendingUnit(int uid);
	bool isAliveMember(int uid) const;

	int consume(int f);
	int getFood() const;

	double getCampRange() const;

	bool isNeutralFaction(int uid) const;
	bool isFriendly(const Object *obj);
	void modifyRelation(int uid, int diff);

	QList<int> getQuests() const;

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	int food;
	QHash<int, int> relations;

	int journalUid;
	Journal *journal;
	QList<int> quests;

	int campUid;
	double campRange;

	QSet<int> unitsUids;
	QList<int> allUnitsUids;
	QSet<int> pendingUids;
};
