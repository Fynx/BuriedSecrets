/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class Mind;

class CampWindow : public QFrame {
	Q_OBJECT
public:
	CampWindow(Mind *mind, DataManager *dataManager);

private:
	static const int EquipmentIndex = 0;
	static const int ConstructorIndex = 1;

	QWidget *createTabWidget();
	void initLayout();

	QTabWidget *tabWidget_;

	QPushButton *closeBtn_;

	Mind *const mind_;
	DataManager *const dataManager_;

signals:
	void exit();
};
