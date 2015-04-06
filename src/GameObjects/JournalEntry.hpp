/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

class JournalEntry : public Object {
public:
	JournalEntry(const Prototype *prototype);

	BS::Type getType() const;

	//TODO feel free to change this string to sth more convenient
	QString getDate() const;
	void setDate(const QString &text);
	void setDate(int d, int m, int y, int hrs = -1, int min = -1);

	QString getText() const;
	void setText(const QString &text);

	QString getTitle() const;
	void setTitle(const QString &title);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	QString date;
	QString text;
	QString title;
};
