#include "ItemConstructor.hpp"
#include "Common/Strings.hpp"

ItemConstructor::ItemConstructor(DataManager *dm)
{
	for (Prototype *proto : dm->getAllPrototypes()){
		if (proto->hasProperty(Properties::Type) && proto->getProperty(Properties::Type).toString() == BS::changeTypeToString(BS::Type::Item))
			allItems.append(proto);
	}
}


QList<Prototype *> ItemConstructor::possibleItems(Equipment *eq)
{
	// If no equipment given - return all the item prototypes
	if (!eq)
		return allItems;

	QList<Prototype *> result;
	QSet<QString> names;

	for (Item *it : eq->getItems())
		names.insert(it->getName());

	for (Prototype *proto : allItems){
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
			result.append(proto);
	}

	return result;
}


Item *ItemConstructor::constructItem(Prototype *, Equipment *eq)
{
	return nullptr;
}
