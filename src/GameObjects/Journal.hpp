/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/JournalEntry.hpp"

//TODO put this journal into Faction

class Mind;
class Unit;
class Item;

class Journal : public Object {
public:
	Journal(const Prototype *prototype);

	BS::Type getType() const;

	void addEntry(JournalEntry *entry);
	JournalEntry *getEntry(int number) const;
	const QVector<JournalEntry *>getEntries() const;
	int getEntriesNumber() const;
	void clearEntries();

	const QVector<int> &getEntriesUids() const;

	//TODO either put date as an argument, or set date afterwards whenever you use these functions.

	JournalEntry *createEntryDeath(Mind *mind, Unit *who);
	JournalEntry *createEntryItemFound(Mind *mind, Unit *who, const QVector<Item *> &what);
	JournalEntry *createEntryQuest(Mind *mind, int entryUid);
	JournalEntry *createEntryPsycho(Mind *mind, Unit *who);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	JournalEntry *createEntry(Mind *mind);

	QVector<int> entriesUids;
	QVector<JournalEntry *> entries;
};