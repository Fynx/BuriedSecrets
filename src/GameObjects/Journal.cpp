/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "GameObjects/Journal.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Item.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"

Journal::Journal(const Prototype *prototype)
	: Object(prototype)
{}

BS::Type Journal::getType() const
{
	return BS::Type::Journal;
}

void Journal::addEntry(JournalEntry *entry)
{
	entries.append(entry);
}

JournalEntry *Journal::getEntry(int number) const
{
	if (entries.size() <= number) {
		warn("Invalid journal entry number.");
		return nullptr;
	}
	return entries[number];
}

const QVector< JournalEntry* > Journal::getEntries() const
{
	return entries;
}

int Journal::getEntriesNumber() const
{
	return entries.size();
}

void Journal::clearEntries()
{
	qDeleteAll(entries);
	entries.clear();
}

const QVector<int> &Journal::getEntriesUids() const
{
	return entriesUids;
}

JournalEntry *Journal::createEntryDeath(Mind *mind, Unit *who)
{
	JournalEntry *entry = createEntry(mind);
	JournalEntry *baseEntry = mind->getEntryFromType(BS::EntryType::Death);

	entry->setTitle(baseEntry->getTitle().arg(who->getName()));

	QString text = baseEntry->getText().arg(who->getName());

	entry->setText(text);
	entry->setEntryType(BS::EntryType::Death);

	return entry;
}

JournalEntry *Journal::createEntryItemFound(Mind *mind, Unit *who, const QVector<Item *> &what)
{
	JournalEntry *entry = createEntry(mind);

	QString itemsString;
	for (Item *item : what) {
		if (!itemsString.isEmpty())
			itemsString.append(", ");
		itemsString.append(item->getName());
	}

	QString title = mind->getEntryFromType(BS::EntryType::ItemFound)->getTitle();
	entry->setTitle(title.arg(itemsString));
	entry->setEntryType(BS::EntryType::ItemFound);
// 	entry->setTitle(who->getName() + " found items: " + itemsString);

	return entry;
}

JournalEntry *Journal::createEntryPsycho(Mind *mind, Unit *who)
{
	JournalEntry *entry = createEntry(mind);

	QString title = mind->getEntryFromType(BS::EntryType::Psycho)->getTitle();
	entry->setTitle(title.arg(who->getName()));
	entry->setEntryType(BS::EntryType::Psycho);
// 	entry->setTitle(who->getName() + " got psychoed. Get mlged scrub");

	return entry;
}

//TODO maybe some optional args, I dunno

JournalEntry *Journal::createEntryQuest(Mind *mind, int entryUid)
{
	JournalEntry *entry = dynamic_cast<JournalEntry *>(mind->getObjectFromUid(entryUid));
	addEntry(entry);
	entry->setEntryType(BS::EntryType::Quest);

	return entry;
}

void Journal::loadFromJson(const QJsonObject &json)
{
	for (const QJsonValue &val : json[Attributes::Entries].toArray())
		entriesUids.append(val.toInt());

	Object::loadFromJson(json);
}

QJsonObject Journal::saveToJson() const
{
	QJsonObject json = Object::saveToJson();

	QJsonArray jEntries;
	for (JournalEntry *entry : entries)
		jEntries.append(entry->getUid());

	json[Attributes::Entries] = jEntries;

	return json;
}

JournalEntry *Journal::createEntry(Mind *mind)
{
	JournalEntry *entry =
		dynamic_cast<JournalEntry *>(mind->createDefaultObject(BS::Type::JournalEntry, "BasicJournalEntry"));
	entry->assignUid();
	addEntry(entry);
	mind->addObject(entry);

	return entry;
}
