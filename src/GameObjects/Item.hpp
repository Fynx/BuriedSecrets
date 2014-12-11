/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

class Item : public Object {
public:
	Item(const Prototype *prototype);

	enum class ItemType {
		Storyline,
		Material,
		Personal,
		Fortification,
	};

	ItemType getItemType() const;
	bool isEquippable() const;

	QString getName() const;
	int getWeight() const;

private:
	static const QMap<ItemType, bool> equippable;
	static const QMap<QString, ItemType> stringToItemType;
};