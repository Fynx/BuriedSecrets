/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/Location.hpp"
#include "Common/Strings.hpp"

Location::Location(const Prototype *prototype)
	: Object(prototype),
	  unitMet(0),
	  exitPoint(0,0)
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

const QMap<Item *, int> &Location::getItemsDifficulty() const
{
	return items;
}

const QMap<int, int> &Location::getItemsUids() const
{
	return itemsUids;
}

void Location::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);

	if (json.contains(Attributes::Items)) {
		for (const QJsonValue &val : json[Attributes::Items].toArray()) {
			int itemUid = val.toObject()[Attributes::Uid].toInt();
			int itemSD  = val.toObject()[Attributes::SearchDifficulty].toInt();
			itemsUids[itemUid] = itemSD;
		}
	}
	if (json.contains(Attributes::Units)) {
		for (const QJsonValue &uid : json[Attributes::Units].toArray())
			unitsUids.insert(uid.toInt());
	}

	if (json.contains(Attributes::UnitMet))
		unitMet = json[Attributes::UnitMet].toInt();
	if (json.contains(Attributes::ExitX) && json.contains(Attributes::ExitY))
		exitPoint = QPointF(json[Attributes::ExitX].toDouble(), json[Attributes::ExitY].toDouble());
}

QJsonObject Location::saveToJson() const
{
	QJsonObject json = Object::saveToJson();

	QJsonArray its;
	for (Item *item : items.keys()) {
		QJsonObject itemEntry;
		itemEntry[Attributes::Uid] = item->getUid();
		itemEntry[Attributes::SearchDifficulty] = items[item];
		its.append(itemEntry);
	}
	if (!its.isEmpty())
		json[Attributes::Items] = its;

	QJsonArray uts;
	for (int unitUid : unitsUids)
		uts.append(unitUid);
	if (!uts.isEmpty())
		json[Attributes::Units] = uts;

	if (unitMet != Object::InvalidUid)
		json[Attributes::UnitMet] = unitMet;

	json[Attributes::ExitX] = exitPoint.x();
	json[Attributes::ExitY] = exitPoint.y();

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

bool Location::isFull() const
{
	return getCapacity() <= unitsUids.count();
}

QPointF Location::getOffset() const
{
	if (prototype->hasProperty(Properties::OffsetX))
		return QPointF(prototype->getProperty(Properties::OffsetX).toFloat(), prototype->getProperty(Properties::OffsetY).toFloat());
	return QPointF(5, 5);
}

QPointF Location::getExitPoint() const
{
	return exitPoint;
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

int Location::getUnitMet()
{
	return unitMet;
}

void Location::setUnitMet(int uid)
{
	unitMet = uid;
}
