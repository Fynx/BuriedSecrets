/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Item.hpp"
#include "Common/Enums.hpp"

Item::Item(const Prototype *prototype)
	: Object(prototype), usesLeft(1), delay(0)
{
}

BS::Type Item::getType() const
{
	return BS::Type::Item;
}

QVector<BS::ItemType> Item::getItemTypes() const
{
	QVector<BS::ItemType> result;
	QList<QVariant> s = prototype->getProperty(Properties::ItemTypes).toList();
	for (const QVariant &val : s) {
		BS::ItemType itemType = BS::changeStringToItemType(val.toString());
		if (itemType == BS::ItemType::Invalid)
			err("Unknown itemType");
		else
			result.append(itemType);
	}
	return result;
}

QString Item::getName() const
{
	return prototype->getProperty(Properties::Name).toString();
}

int Item::getWeight() const
{
	return prototype->getProperty(Properties::Weight).toInt();
}

QSet<BS::Slot> Item::getAvailableSlots() const
{
	QSet<BS::Slot> result;
	for (BS::ItemType itemType : getItemTypes())
		result.insert(BS::getCorrespondingSlot(itemType));
	return result;
}

bool Item::isSlotAvailable(BS::Slot slot) const
{
	return getAvailableSlots().contains(slot);
}

int Item::getUseDelay()
{
	return delay;
}

void Item::setUseDelay(int t)
{
	delay = t;
}

int Item::getUsesLeft()
{
	return usesLeft;
}

void Item::setUsesLeft(int n)
{
	usesLeft = n;
	if (usesLeft < 0)
		usesLeft = 0;
}

void Item::loadFromJson(const QJsonObject &json)
{
	Object::loadFromJson(json);
}

QJsonObject Item::saveToJson() const
{
	return Object::saveToJson();
}
