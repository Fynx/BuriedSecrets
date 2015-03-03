/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "UserInterface/ItemsDisplay.hpp"

class DataManager;
class Unit;

class UnitEquipmentTab : public ItemsDisplay {

public:
	UnitEquipmentTab(Unit *unit, DataManager *dataManager);

private:
	void initLayout();

	Unit *unit_;
};
