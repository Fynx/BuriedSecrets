/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class BriefingTab;
class CampConstructorTab;
class CampEquipmentTab;
class DataManager;
class Mind;

/**
 * In-game window to display info about player's faction.
 */
class CampWindow : public QFrame {
	Q_OBJECT
public:
	static const int EquipmentIndex   = 0;
	static const int BriefingIndex    = 1;
	static const int ConstructorIndex = 2;

	CampWindow(Mind *mind, DataManager *dataManager);
	void refresh();
	void setCurrentTab(int tabIndex);

private:

	QWidget *createTabWidget();
	void initLayout();

	QTabWidget *tabWidget_;

	QPushButton *closeBtn_;

	Mind *const mind_;
	DataManager *const dataManager_;

	CampEquipmentTab *campEquipmentTab_;
	BriefingTab *briefingTab_;
	CampConstructorTab *campConstructorTab_;

signals:
	void exit();
};
