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
	for (QJsonValue val : json[Properties::Items].toArray())
		itemsUids.insert(val.toInt());
}

QJsonObject Equipment::saveToJson() const
{
	QJsonObject json = Object::saveToJson();
	QJsonArray itms;
	for (int itemUid : itemsUids)
		itms.append(itemUid);
	json[Properties::Items] = itms;
	return json;
}

Item *Equipment::getSlotItem(BS::Slot slot)
{
	if ((!usedItems.contains(slot)) || (!items.contains(usedItems[slot])))
		return nullptr;
	return usedItems.value(slot);
}
