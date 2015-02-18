/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Unit;

class UnitWindow : public QFrame {
	Q_OBJECT
public:
	UnitWindow();

public slots:
	void setUnit(Unit *unit);

private:
	static const int EquipmentIndex = 0;
	static const int HistoryIndex = 1;
	static const int StatsIndex = 2;

	void initLayout();

	Unit *unit_;

	QTabWidget *tabWidget_;

	QLabel *title_;
	QPushButton *closeBtn_;

signals:
	void exit();
};
