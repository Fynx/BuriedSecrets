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

const QSet<int> &Location::getItemsUids() const
{
	return itemsUids;
}

//TODO Search difficulty

void Location::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);

	assemblable = (bool) json[Properties::Assemblable].toInt();
	transparent = (bool) json[Properties::Transparent].toInt();
	capacity = json[Properties::Capacity].toInt();
	rangeOfHealing = json[Properties::Range].toDouble();

	if (json.contains(Attributes::Items)) {
		for (const QJsonValue &uid : json[Attributes::Items].toArray())
			itemsUids.insert(uid.toInt());
	}
	if (json.contains(Attributes::Units)) {
		for (const QJsonValue &uid : json[Attributes::Units].toArray())
			unitsUids.insert(uid.toInt());
	}
}

QJsonObject Location::saveToJson() const
{
	QJsonObject json = Object::saveToJson();

	if (assemblable)
		json[Properties::Assemblable] = (int) assemblable;
	if (transparent)
		json[Properties::Transparent] = (int) transparent;
	if (capacity)
		json[Properties::Capacity] = capacity;
	if (rangeOfHealing != 0)
		json[Properties::Range] = rangeOfHealing;

	QJsonArray its;
	for (Item *item : items.keys())
		its.append(item->getUid());
	if (!its.isEmpty())
		json[Attributes::Items] = its;

	QJsonArray uts;
	for (int unitUid : unitsUids)
		uts.append(unitUid);
	if (!uts.isEmpty())
		json[Attributes::Units] = uts;

	return json;
}

void Location::insertUnit(int id)
{
	unitsUids.insert(id);
}

void Location::removeUnit(int id)
{
	unitsUids.remove(id);
}

QList<int> Location::getUnitsUids() const
{
	return unitsUids.toList();
}

QPointF Location::getOffset()
{
	return offset;
}

bool Location::isAssemblable() const
{
	return assemblable;
}

bool Location::isTransparent() const
{
	return transparent;
}

int Location::getCapacity() const
{
	return capacity;
}

qreal Location::getRange() const
{
	return rangeOfHealing;
}
