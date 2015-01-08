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
	void removeItem(int searchDifficulty, Item *item);
	QMultiMap<int, Item *> getItems() const;

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;
private:

	QMultiMap<int, Item *> items;
};