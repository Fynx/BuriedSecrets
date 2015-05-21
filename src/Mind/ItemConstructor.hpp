/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "DataManager/DataManager.hpp"
#include "GameObjects/Equipment.hpp"


class Mind;

/**
 * @class ItemConstructor
 * Convenience class for Mind, used for constructing items.
 */
class ItemConstructor {

public:
	ItemConstructor(DataManager *, Mind *);
	/** Returns the set of Items that can be constructed out of what is in given Equipment. */
	QSet<const Prototype *> possibleItems(Equipment *eq = nullptr);
	/** Creates new Item and removes required ingredients from given Equipment. */
	Item *constructItem(const Prototype *, Equipment *eq);

private:
	QSet<const Prototype *> allItems;
	Mind *mind;
};
