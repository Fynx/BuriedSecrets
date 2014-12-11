/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Item.hpp"
#include "GameObjects/Location.hpp"

class Building : public Object, public Location {
public:
	Building(const Prototype *prototype);

	Object::Type getType() const;

	void addItem(int searchDifficulty, Item *item);
	void removeItem(int searchDifficulty, Item *item);
	QMultiMap<int, Item *> getItems() const;

private:
	friend QDataStream &operator<<(QDataStream &out, const Building &building);
	friend QDataStream &operator>>(QDataStream &in, Building &building);

	QMultiMap<int, Item *> items;
};