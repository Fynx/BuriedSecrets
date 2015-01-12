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
	QList<Prototype *> possibleItems(Equipment *eq = nullptr);
	Item *constructItem(Prototype *, Equipment *eq);

private:
	QList<Prototype *> allItems;
	Mind *mind;
};
