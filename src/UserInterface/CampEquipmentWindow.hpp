/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class CampEquipmentWindow : public QFrame {
public:
	CampEquipmentWindow();

private:
	void initLayout();

	QPushButton *closeBtn_;
};
