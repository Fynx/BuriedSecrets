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
	void initLayout();

	QPushButton *closeBtn_;

signals:
	void exit();
};
