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
	const QMap<Item *, int> &getItemsDifficulty() const;
	const QMap<int, int> &getItemsUids() const;

	void insertUnit(int id);
	void removeUnit(int id);
	QList<int> getUnitsUids() const;

	QPointF getOffset();

	bool isAssemblable() const;
	bool isTransparent() const;
	int getCapacity() const;
	qreal getRange() const;

	void setRange(qreal r);		// REMOVE
	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	/** Items, searchDifficulty */
	QMap<Item *, int> items;
	QMap<int, int> itemsUids;
	QSet<int> unitsUids;

	bool assemblable;
	bool transparent;
	int capacity;
	qreal range;
};
