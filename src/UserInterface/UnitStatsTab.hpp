/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Unit;

class UnitStatsTab : public QWidget {

public:
	UnitStatsTab(Unit *unit);

private:
	void initLayout();
	Unit *unit_;

};
