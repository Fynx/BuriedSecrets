/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Unit;

class UnitHistoryTab : public QWidget {

public:
	UnitHistoryTab(Unit *unit);

private:
	void initLayout();

	Unit *unit_;
};
