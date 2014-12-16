/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

class Item : public Object {
public:
	Item(const Prototype *prototype);

	BS::ItemType getItemType() const;
	bool isEquippable() const;

	QString getName() const;
	int getWeight() const;

private:
	static const QMap<BS::ItemType, bool> equippable;
	static const QMap<QString, BS::ItemType> stringToItemType;
};