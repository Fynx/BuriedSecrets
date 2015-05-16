/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"
#include "GameObjects/Equipment.hpp"

class Journal;
class Location;
class Unit;

/**
 * @class Faction
 * Objects can have their Factions - that's particularly important for Units.
 * This class provides functions that allow to do operations on all Units in the Faction,
 * manage Faction-related variables and interact with other Factions.
 */
class Faction : public Object, public Equipped {
public:
	Faction(const Prototype *prototype);

	BS::Type getType() const;

	/** Faction can have a Journal, where some events and messages are stored. */
	int getJournalUid() const;
	void setJournal(Journal *journal);

	Journal *getJournal();

	/** Camp is a Location/Item Object. No more than one per Faction. */
	int getCampUid() const;
	void setCamp(int);

	/** Unit management functions. */
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

	/** Faction relations management functions. */
	bool isNeutralFaction(int uid) const;
	bool isFriendly(const Object *obj);
	void modifyRelation(int uid, int diff);

	/** List of Quest Objects that belong to this Faction. */
	QList<int> getQuests() const;

	int getTotalFrags() const;
	void incTotalFrags();

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	int food;
	QHash<int, int> relations;

	int journalUid;
	Journal *journal;
	QList<int> quests;

	int totalFrags;

	int campUid;
	double campRange;

	QSet<int> unitsUids;
	QList<int> allUnitsUids;
	QSet<int> pendingUids;
};
