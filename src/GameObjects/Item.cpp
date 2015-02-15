/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Common/Strings.hpp"
#include "GameObjects/Item.hpp"

Item::Item(const Prototype *prototype)
	: Object(prototype)
{
}

BS::Type Item::getType() const
{
	return BS::Type::Unit;
}

BS::ItemType Item::getItemType() const
{
	QString s = prototype->getProperty(Properties::ItemType).toString();
	if (!stringToItemType.contains(s)) {
		qDebug() << "Unknown itemType";
		exit(0);
	}
	return stringToItemType[s];
}

bool Item::isEquippable() const
{
	return equippable[getItemType()];
}

QString Item::getName() const
{
	return prototype->getProperty(Properties::Name).toString();
}

int Item::getWeight() const
{
	return prototype->getProperty(Properties::Weight).toInt();
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

const QMap<BS::ItemType, bool> Item::equippable {
	{BS::ItemType::Storyline,     true},
	{BS::ItemType::Material,      false},
	{BS::ItemType::Personal,      true},
	{BS::ItemType::Fortification, true},
};

const QMap<QString, BS::ItemType> Item::stringToItemType {
	{"storyline",     BS::ItemType::Storyline},
	{"material",      BS::ItemType::Material},
	{"personal",      BS::ItemType::Personal},
	{"fortification", BS::ItemType::Fortification},
};
