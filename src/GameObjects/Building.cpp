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
	items.insert(searchDifficulty, item);
}

void Building::removeItem(int searchDifficulty, Item *item)
{
	auto it = items.begin();
	while (it != items.end() && (it.key() != searchDifficulty || it.value() != item))
		++it;
	if (it == items.end())
		qDebug() << "Failed to remove item";
	else
		items.erase(it);
}

QMultiMap<int, Item *> Building::getItems() const
{
	return items;
}

QDataStream &operator<<(QDataStream &out, const Building &building)
{
	out << dynamic_cast<const Object &>(building);
	return out;
}

QDataStream &operator>>(QDataStream &in, Building &building)
{
	in >> dynamic_cast<Object &>(building);
	return in;
}
