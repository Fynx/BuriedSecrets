/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Mind;
class UnitWidget;

class UnitsPanel : public QFrame{
public:
	UnitsPanel();
	QSize sizeHint() const;
	void update(const Mind *mind);

private:
	void addUnitWidget(UnitWidget *unitWidget);

	//it may render obsolete in the future
	QList <UnitWidget *> unitWidgets_;
};
