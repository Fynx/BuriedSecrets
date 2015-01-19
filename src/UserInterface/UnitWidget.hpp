/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class Unit;
class Mind;

static const QSize WidgetSize{210, 120};

class UnitWidget : public QFrame {
	Q_OBJECT
public:
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
	QFrame *face_;
	QLabel *name_;
	QProgressBar *hpBar_;
	QProgressBar *psychosisBar_;
	QProgressBar *encumbranceBar_;
	QLabel *behaviourLabel_;

signals:
	void select();
	void add();
	void heal();
	void showUnit();
	void showMenu();
};
