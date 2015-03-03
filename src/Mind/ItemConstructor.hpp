/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "DataManager/DataManager.hpp"
#include "GameObjects/Equipment.hpp"


class Mind;

class ItemConstructor {

public:
	ItemConstructor(DataManager *, Mind *);
	QSet<const Prototype *> possibleItems(Equipment *eq = nullptr);
	Item *constructItem(const Prototype *, Equipment *eq);

private:
	QSet<const Prototype *> allItems;
	Mind *mind;
};
