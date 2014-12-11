/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/JournalEntry.hpp"

class Journal : public Object {
public:
	Journal(const Prototype *prototype);

	void addEntry(JournalEntry *entry);
	JournalEntry *getEntry(int number) const;
	void clearEntries();

private:
	QVector<JournalEntry *> entries;
};