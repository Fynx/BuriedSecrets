/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Item.hpp"

class Location : public Object {
public:
	Location(const Prototype *prototype);
	virtual ~Location();

	BS::Type getType() const;

	void addItem(int searchDifficulty, Item *item);
	void removeItem(Item *item);
	QList<Item *> getItems(int searchDifficulty = 1000) const;

	void insertUnit(int id);
	void removeUnit(int id);
	QList<int> getUnits() const;

	QPointF getOffset();

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	QPointF offset;
	QMap<Item *, int> items;
	QSet<int> units;
};
