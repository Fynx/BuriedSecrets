#include "GameObjects/Journal.hpp"

Journal::Journal(const Prototype *prototype)
	: Object(prototype)
{}

void Journal::addEntry(JournalEntry *entry)
{
	entries.append(entry);
}

JournalEntry *Journal::getEntry(int number) const
{
	return entries[number];
}

void Journal::clearEntries()
{
	qDeleteAll(entries);
	entries.clear();
}
