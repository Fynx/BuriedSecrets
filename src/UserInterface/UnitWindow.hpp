/* YoLoDevelopment, 2015
 * All rights reserved.
 */

#pragma once

#include <QtWidgets>

class Mind;
class Unit;

class UnitWindow : public QFrame {
	Q_OBJECT
public:
	UnitWindow(Mind *mind);

public slots:
	void setUnit(int uid);

private:
	void initLayout();

	Mind *mind_;
	Unit *unit_;
	QLabel *title_;
	QPushButton *closeBtn_;

signals:
	void exit();
};
