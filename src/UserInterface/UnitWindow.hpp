/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class Unit;

class UnitWindow : public QFrame {
	Q_OBJECT
public:
	UnitWindow(DataManager *dataManager);

public slots:
	void setUnit(Unit *unit);

private:
	static const int EquipmentIndex = 0;
	static const int HistoryIndex = 1;

	void initLayout();

	Unit *unit_;
	DataManager *const dataManager_;

	QTabWidget *tabWidget_;

	QLabel *title_;
	QPushButton *closeBtn_;

signals:
	void exit();
};
