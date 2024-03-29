/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Item.hpp"
#include "Common/Enums.hpp"

/**
 * @class Equipment
 * Storage class for the Items.
 * Provides convenience functions.
 */
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

	//TODO AEIOU list below should be read from prototype according to class or sth
	// may be const &
	/**
	 * Except for storing the set of items in general, Equipment class provides putting certain items in slots.
	 */
	QList<BS::Slot> getAvailableSlots();
	void removeFromSlot(BS::Slot slot);
	void putItemIntoSlot(BS::Slot slot, Item *item);
	int getSlotItemUid(BS::Slot slot) const;
	Item *getSlotItem(BS::Slot slot) const;

	virtual void loadFromJson(const QJsonObject &json);
	virtual QJsonObject saveToJson() const;

private:
	QSet<int> itemsUids;
	QSet<Item *> items;
	QHash<BS::Slot, int> usedItemsUids;
	QHash<BS::Slot, Item *> usedItems;
};

/**
 * @class Equipped
 * Convenience class for anything that contains Equipment.
 * A subclass of Object can derive from Equipped.
 */
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
