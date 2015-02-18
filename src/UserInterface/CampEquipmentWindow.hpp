/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class CampEquipmentWindow : public QFrame {
	Q_OBJECT
public:
	CampEquipmentWindow();

private:
	QWidget *createTabWidget();
	void initLayout();

	QTabWidget *tabWidget_;
	QWidget *equipmentTab_;
	QWidget *constructorTab_;

	QPushButton *closeBtn_;

signals:
	void exit();
};
