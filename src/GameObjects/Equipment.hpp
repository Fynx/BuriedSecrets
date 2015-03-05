/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Item.hpp"
#include "Common/Enums.hpp"

class Equipment : public Object {
public:
	Equipment(const Prototype *prototype);

	virtual bool isRemovable() const;
	virtual BS::Type getType() const;

	bool isEmpty() const;
	void addItem(Item *item);
	void removeItem(Item *item);
	const QSet<int> &getItemsUids() const;
	const QSet<Item *> &getItems() const;
	int getWeight() const;

	void removeFromSlot(BS::Slot slot);
	void putItemIntoSlot(BS::Slot slot, Item *item);
	int getSlotItemUid(BS::Slot slot) const;
	Item *getSlotItem(BS::Slot slot);
	const Item *getSlotItem(BS::Slot slot) const;

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	QSet<int> itemsUids;
	QSet<Item *> items;
	QHash<BS::Slot, int> usedItemsUids;
	QHash<BS::Slot, Item *> usedItems;
};

class Equipped {
public:
	Equipment *getEquipment();
	const Equipment *getEquipment() const;
	void setEquipment(Equipment *eq);
	int getEquipmentUid() const;

	void loadFromJson(const QJsonObject &json);
	QJsonObject saveToJson() const;

private:
	Equipment *equipment;
	int equipmentUid;
};
