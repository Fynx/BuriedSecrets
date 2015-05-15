/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class Mind;
class Unit;

/**
 * In-game window to display information about specific unit.
 */
class UnitWindow : public QFrame {
	Q_OBJECT
public:
	UnitWindow(Mind *mind, DataManager *dataManager);

public slots:
	void setUnit(Unit *unit);
	void setUnitForDecision(int uid);

private:
	static const int ShowMode = 0;
	static const int DecisionMode = 1;
	static const int EquipmentIndex = 0;
	static const int HistoryIndex = 1;
	static const QFont LabelFont;

	void initLayout();
	QWidget *createShowButtons();
	QWidget *createDecisionButtons();

	Unit *unit_;
	Mind *const mind_;
	DataManager *const dataManager_;

	QTabWidget *tabWidget_;

	QLabel *title_;

	QStackedLayout *buttonsLayout_;

private slots:
	void onAccept();
	void onDecline();

signals:
	void exit();
};
