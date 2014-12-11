/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Equipment.hpp"

Equipment::Equipment(const Prototype *prototype)
	: Object(prototype)
{}

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
