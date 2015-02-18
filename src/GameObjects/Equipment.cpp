/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Equipment.hpp"

Equipment::Equipment(const Prototype *prototype)
	: Object(prototype)
{}

BS::Type Equipment::getType() const
{
	return BS::Type::Equipment;
}

void Equipment::addItem(Item *item)
{
	if (item == nullptr) {
		warn("Trying to add null item.");
		return;
	}
	items.insert(item);
	itemsUids.insert(item->getUid());
}

void Equipment::removeItem(Item *item)
{
	items.remove(item);
}

const QSet<int> &Equipment::getItemsUids() const
{
	return itemsUids;
}

const QSet<Item *> &Equipment::getItems() const
{
	return items;
}

int Equipment::getWeight() const
{
	int weight = 0;
	for (Item *item : items)
		weight += item->getWeight();
	return weight;
}

void Equipment::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
	for (QJsonValue val : json[Attributes::Items].toArray())
		itemsUids.insert(val.toInt());
	for (const QString &key : json[Attributes::Slots].toObject().keys())
		usedItemsUids[BS::changeStringToSlot(key)] = json[Attributes::Slots].toObject()[key].toInt();
}

QJsonObject Equipment::saveToJson() const
{
	QJsonObject json = Object::saveToJson();

	QJsonArray itms;
	for (int itemUid : itemsUids)
		itms.append(itemUid);
	json[Attributes::Items] = itms;

	QJsonObject used;
	for (BS::Slot slot : usedItemsUids.keys())
		used[BS::changeSlotToString(slot)] = usedItemsUids[slot];
	json[Attributes::Slots] = used;

	return json;
}

void Equipment::putItemIntoSlot(BS::Slot slot, Item *item)
{
	if (!items.contains(item)) {
		err("Item must be inserted into the equipment, before it can be attached to the slot!");
		return;
	}
	usedItems[slot] = item;
	usedItemsUids[slot] = item->getUid();
}

int Equipment::getSlotItemUid(BS::Slot slot) const
{
	if (!usedItemsUids.contains(slot))
		return Object::InvalidUid;
	return usedItemsUids[slot];
}

Item *Equipment::getSlotItem(BS::Slot slot)
{
	if ((!usedItems.contains(slot)) || (!items.contains(usedItems[slot])))
		return nullptr;
	return usedItems.value(slot);
}
