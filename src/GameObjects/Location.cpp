/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Location.hpp"
#include "Common/Strings.hpp"

Location::Location(const Prototype *prototype)
	: Object(prototype)
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

	rangeOfHealing = json[Attributes::CampRange].toDouble();

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

	if (rangeOfHealing != 0)
		json[Attributes::CampRange] = rangeOfHealing;

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
	if (prototype->hasProperty(Properties::OffsetX))
		return QPointF(prototype->getProperty(Properties::OffsetX).toFloat(), prototype->getProperty(Properties::OffsetY).toFloat());
	return QPointF(5, 5);
}

bool Location::isAssemblable() const
{
	return prototype->getProperty(Properties::Assemblable).toBool();
}

bool Location::isTransparent() const
{
	return prototype->getProperty(Properties::Transparent).toBool();
}

int Location::getCapacity() const
{
	return prototype->getProperty(Properties::Capacity).toInt();
}

qreal Location::getRange() const
{
	return rangeOfHealing;
}
