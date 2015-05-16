/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

/**
 * @class JournalEntry
 * Entries in Journal.
 * Contain information about what is happening in the game,
 * including Units' deaths, Quest entries and so on.
 * JournalEntries contain date, text and title.
 */
class JournalEntry : public Object {
public:
	static bool hasLongForm(BS::EntryType type);
	static bool hasNotification(BS::EntryType type);

	JournalEntry(const Prototype *prototype);

	BS::Type getType() const;

	QString getDate() const;
	void setDate(const QString &text);
	void setDate(int d, int m, int y, int hrs = -1, int min = -1);

	QString getText() const;
	void setText(const QString &text);

	QString getTitle() const;
	void setTitle(const QString &title);

	/** What kind of Entry is this. Quest? Help-related? */
	BS::EntryType getEntryType() const;
	void setEntryType(BS::EntryType type);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	QString date;
	QString text;
	QString title;
	BS::EntryType entryType;
};
