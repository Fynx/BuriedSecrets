/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Location.hpp"
#include "Common/Strings.hpp"

Location::Location(const Prototype *prototype)
	: Object(prototype), offset(-1, 0.5)
{}

Location::~Location()
{}

BS::Type Location::getType() const
{
	return BS::Type::Location;
}

void Location::addItem(int searchDifficulty, Item *item)
{
	items.insert(item, searchDifficulty);
}

void Location::removeItem(Item *item)
{
	items.remove(item);
}

QList<Item *> Location::getItems(int searchDifficulty) const
{
	QList<Item *> result;
	for (auto it : items.keys()){
		if (items.value(it) <= searchDifficulty)
			result.append(it);
	}

	return result;
}

void Location::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
	rangeOfHealing = json[Properties::Range].toDouble();
	//TODO
}

QJsonObject Location::saveToJson() const
{
	//TODO
	QJsonObject json = Object::saveToJson();

	if (rangeOfHealing != 0)
		json[Properties::Range] = rangeOfHealing;

	return json;
}

void Location::insertUnit(int id)
{
	units.insert(id);
}

void Location::removeUnit(int id)
{
	units.remove(id);
}

QList<int> Location::getUnits() const
{
	return units.toList();
}

QPointF Location::getOffset()
{
	return offset;
}

qreal Location::getRange() const
{
	return rangeOfHealing;
}
