/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "GameObjects/Item.hpp"

Item::Item(const Prototype *prototype)
	: Object(prototype)
{}

BS::ItemType Item::getItemType() const
{
	QString s = prototype->getProperty("itemType").toString();
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
	return prototype->getProperty("name").toString();
}

int Item::getWeight() const
{
	return prototype->getProperty("weight").toInt();
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
