/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Mind;

static const QSize CampPanelSize{300, 100};

class CampPanel : public QFrame {
	Q_OBJECT
public:
	CampPanel();
	void update(const Mind *mind);

private:
	void initWidgets();
	void initLayout();
	void setFoodAmount(int food);

	QPushButton *campEquipmentBtn_;
	QPushButton *journalBtn_;
	QLabel *foodLabel_;

signals:
	void journalActivated();
	void campEQActivated();
};
