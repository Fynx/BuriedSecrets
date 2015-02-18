/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Item.hpp"
#include "Common/Enums.hpp"

class Equipment : public Object {
public:
	Equipment(const Prototype *prototype);

	virtual BS::Type getType() const;

	void addItem(Item *item);
	void removeItem(Item *item);
	const QSet<int> &getItemsUids() const;
	const QSet<Item *> &getItems() const;
	int getWeight() const;
	
	void putItemIntoSlot(BS::Slot slot, Item *item);
	int getSlotItemUid(BS::Slot slot) const;
	Item *getSlotItem(BS::Slot slot);

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	QSet<int> itemsUids;
	QSet<Item *> items;
	QHash<BS::Slot, int> usedItemsUids;
	QHash<BS::Slot, Item *> usedItems;
};
