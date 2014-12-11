/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "GameObjects/Item.hpp"

Item::Item(const Prototype *prototype)
	: Object(prototype)
{}

Item::ItemType Item::getItemType() const
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

const QMap<Item::ItemType, bool> Item::equippable {
	{ItemType::Storyline,     true},
	{ItemType::Material,      false},
	{ItemType::Personal,      true},
	{ItemType::Fortification, true},
};

const QMap<QString, Item::ItemType> Item::stringToItemType {
	{"storyline",     ItemType::Storyline},
	{"material",      ItemType::Material},
	{"personal",      ItemType::Personal},
	{"fortification", ItemType::Fortification},
};
