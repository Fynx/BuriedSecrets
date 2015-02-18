/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Unit;

class UnitEquipmentTab : public QWidget {

public:
	UnitEquipmentTab(Unit *unit);

private:
	void initLayout();
	Unit *unit_;

};
