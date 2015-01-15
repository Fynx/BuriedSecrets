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
	QSize sizeHint() const;
	void refresh();

private:
	void initWidgets();
	void initLayout();

	const Unit* unit_;

	QFrame *campIcon_;
	QFrame *locationIcon_;
	QPushButton *face_;
	QLabel *name_;
	QProgressBar *hpBar_;
	QProgressBar *psychosisBar_;
	QProgressBar *encumbranceBar_;
	QLabel *behaviourLabel_;

signals:
	void selected();
};
