/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Item.hpp"

/**
 * @class Location
 * An Object visible on the map.
 * Unit might or might not be able to enter a Location.
 * Locations may contain Items to be found.
 */
class Location : public Object {
public:
	Location(const Prototype *prototype);
	virtual ~Location();

	BS::Type getType() const;

	/** Item management functions. */
	void addItem(int searchDifficulty, Item *item);
	void removeItem(Item *item);
	QList<Item *> getItems(int searchDifficulty = 1000) const;
	const QMap<Item *, int> &getItemsDifficulty() const;
	const QMap<int, int> &getItemsUids() const;

	/** Unit management functions. */
	void insertUnit(int id);
	void removeUnit(int id);
	QList<int> getUnitsUids() const;
	bool isFull() const;

	QPointF getOffset() const;

	QPointF getExitPoint() const;

	/** Is it possible to construct the Location from components. */
	bool isAssemblable() const;
	/** Can a Unit see through this location. */
	bool isTransparent() const;
	int getCapacity() const;

	/** Unit that might wait in the Location. */
	int getUnitMet();
	void setUnitMet(int uid);

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
	int unitMet;
	QPointF exitPoint;
};
