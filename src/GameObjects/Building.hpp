/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Item.hpp"
#include "GameObjects/Location.hpp"

class Building : public Object, public Location {
public:
	Building(const Prototype *prototype);

	BS::Type getType() const;

	void addItem(int searchDifficulty, Item *item);
	void removeItem(Item *item);
	QList<Item *> getItems(int searchDifficulty = 1000) const;

	void insertUnit(int id);
	void removeUnit(int id);
	QList<int> getUnits();

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	QMap<Item *, int> items;
	QSet<int> units;
};
