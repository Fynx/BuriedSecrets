/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/JournalEntry.hpp"

bool JournalEntry::hasLongForm(BS::EntryType type)
{
	if (type == BS::EntryType::ItemFound)
		return false;
	return true;
}

bool JournalEntry::hasNotification(BS::EntryType type)
{
	if (type == BS::EntryType::Help)
		return false;
	return true;
}


JournalEntry::JournalEntry(const Prototype *prototype)
	: Object(prototype)
{}

BS::Type JournalEntry::getType() const
{
	return BS::Type::JournalEntry;
}

QString JournalEntry::getDate() const
{
	return date;
}

void JournalEntry::setDate(const QString &text)
{
	date = text;
}

//TODO test it

void JournalEntry::setDate(int d, int m, int y, int hrs, int min)
{
	QString timeString = (hrs < 0)
		? ""
		: QString::number(hrs) + (min < 0
			? ""
			: QString(":") + QString::number(min));

	return setDate(QString::number(d) + "." + QString::number(m) + "." + QString::number(y) + " " + timeString);
}

QString JournalEntry::getText() const
{
	return text;
}

void JournalEntry::setText(const QString &newText)
{
	text = newText;
}

QString JournalEntry::getTitle() const
{
	return title;
}

void JournalEntry::setTitle(const QString &newTitle)
{
	title = newTitle;
}

BS::EntryType JournalEntry::getEntryType() const
{
	return entryType;
}

void JournalEntry::setEntryType(BS::EntryType type)
{
	entryType = type;
}

void JournalEntry::loadFromJson(const QJsonObject &json)
{
	date  = json[Attributes::Date].toString();
	text  = json[Attributes::Text].toString();
	title = json[Attributes::Title].toString();

	if (!json.contains(Attributes::EntryType))
		err("No entry type for this JournalEntry!");
	else
		entryType = BS::changeStringToEntryType(json[Attributes::EntryType].toString());

	Object::loadFromJson(json);
}

QJsonObject JournalEntry::saveToJson() const
{
	QJsonObject json = Object::saveToJson();

	json[Attributes::Date]  = date;
	json[Attributes::Text]  = text;
	json[Attributes::Title] = title;
	json[Attributes::EntryType] = BS::changeEntryTypeToString(entryType);

	return json;
}
