/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Common/Strings.hpp"
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

BS::ItemType Item::getItemType() const
{
	QString s = prototype->getProperty(Properties::ItemType).toString();
	if (BS::changeStringToItemType(s) == BS::ItemType::Invalid) {
		qDebug() << "Unknown itemType";
		exit(0);
	}
	return BS::changeStringToItemType(s);
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
	if (!prototype->hasProperty(Properties::Slots))
		return result;
	QVariantList arr = prototype->getProperty(Properties::Slots).toList();
	for (const QVariant &val : arr)
		result.insert(BS::changeStringToSlot(val.toString()));
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
