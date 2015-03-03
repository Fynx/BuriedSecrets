/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "ItemConstructor.hpp"
#include "Common/Strings.hpp"
#include "Mind/Mind.hpp"
#include "GameObjects/Item.hpp"


ItemConstructor::ItemConstructor(DataManager *dm, Mind *m) : mind(m)
{
	for (const Prototype *proto : dm->getAllPrototypes()){
		if (proto->hasProperty(Properties::Type)
			&& proto->getProperty(Properties::Type).toString() == BS::changeTypeToString(BS::Type::Item))
			allItems.insert(proto);
	}
}

QSet<const Prototype *> ItemConstructor::possibleItems(Equipment *eq)
{
	// If no equipment given - return all the item prototypes
	if (!eq)
		return allItems;

	QSet<const Prototype *> result;
	QSet<QString> names;

	for (Item *it : eq->getItems())
		names.insert(it->getName());

	for (auto proto : allItems){
		if (!proto->hasProperty(Properties::Ingredients))
			continue;

		bool isPossible = true;
		for (QString ing : proto->getProperty(Properties::Ingredients).toStringList()){
			if (!names.contains(ing)){
				isPossible = false;
				break;
			}
		}
		if (isPossible)
			result.insert(proto);
	}

	return result;
}

Item *ItemConstructor::constructItem(const Prototype *proto, Equipment *eq)
{
	Item *result;
	// Add Ingredients consumption
	result = new Item(proto);
	mind->addObject(result);
	eq->addItem(result);
	return result;
}
