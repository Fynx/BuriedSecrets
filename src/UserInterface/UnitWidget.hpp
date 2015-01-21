/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Unit;
class Mind;


class UnitWidget : public QFrame {
	Q_OBJECT
public:
	static const QSize WidgetSize;

	UnitWidget(const Unit *unit);

	const Unit *unit();
	QSize sizeHint() const;
	void refresh();

private:
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);

	void initWidgets();
	void initLayout();

	const Unit* unit_;

	QFrame *campIcon_;
	QFrame *locationIcon_;
	QFrame *behaviourIcon_;
	QFrame *face_;
	QLabel *name_;
	QProgressBar *hpBar_;
	QProgressBar *psychosisBar_;

signals:
	void select();
	void add();
	void heal();
	void showUnit();
	void showMenu();
};
