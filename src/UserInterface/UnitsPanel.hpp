/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class UnitWidget;

class UnitsPanel : public QFrame{
public:
	UnitsPanel();
	QSize sizeHint() const;
	void addUnitWidget(UnitWidget *unitWidget);

private:
	//it may render obsolete in the future
	QList <UnitWidget *> unitWidgets_;
};
