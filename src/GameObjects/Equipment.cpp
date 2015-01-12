/* YoLoDevelopment, 2014
 * All rights reserved.
 */
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
	items.insert(item);
}

void Equipment::removeItem(Item *item)
{
	items.remove(item);
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
}

QJsonObject Equipment::saveToJson() const
{
	return Object::saveToJson();
}

Item *Equipment::getSlotItem(BS::Slot slot)
{
	if ((!usedItems.contains(slot)) || (!items.contains(usedItems[slot])))
		return nullptr;
	return usedItems.value(slot);
}
