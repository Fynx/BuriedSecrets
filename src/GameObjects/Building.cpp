/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Building.hpp"

Building::Building(const Prototype *prototype)
	: Object(prototype)
{}

BS::Type Building::getType() const
{
	return BS::Type::Building;
}

void Building::addItem(int searchDifficulty, Item *item)
{
	items.insert(item, searchDifficulty);
}

void Building::removeItem(Item *item)
{
	items.remove(item);
}

QList<Item *> Building::getItems(int searchDifficulty) const
{
	QList<Item *> result;
	for (auto it : items.keys()){
		if (items.value(it) <= searchDifficulty)
			result.append(it);
	}

	return result;
}

void Building::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
}

QJsonObject Building::saveToJson() const
{
	return Object::saveToJson();
}

void Building::insertUnit(int id)
{
	units.insert(id);
}

void Building::removeUnit(int id)
{
	units.remove(id);
}

QList<int> Building::getUnits()
{
	return units.toList();
}
