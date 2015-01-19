/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Mind;
class UnitWidget;

class UnitsPanel : public QFrame {
	Q_OBJECT
public:
	UnitsPanel();
	QSize sizeHint() const;
	void refresh(const Mind *mind);

private:
	void addUnitWidget(UnitWidget *unitWidget);

	QList <UnitWidget *> unitWidgets_;
	QSignalMapper selectSignalMapper_;
	QSignalMapper addSignalMapper_;
	QSignalMapper healSignalMapper_;
	QSignalMapper showMenuSignalMapper_;
	QSignalMapper showUnitSignalMapper_;

signals:
	void addUnit(int uid);
	void healUnit(int uid);
	void selectUnit(int uid);
	void showUnit(int uid);
	void showUnitMenu(int uid);
	void sizeChanged();
};
