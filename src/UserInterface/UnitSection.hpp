/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class Unit;
class Mind;

class UnitSection : public QFrame {
	Q_OBJECT
public:
	static const QSize WidgetSize;

	UnitSection(const Unit *unit, DataManager *dataManager);

	const Unit *unit();
	QSize sizeHint() const;
	void refresh();

private:
	static const QSize AvatarSize;

	void mouseDoubleClickEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);

	void initLayout();
	QLayout *createIconsLayout();
	QLayout *createBarsLayout();
	QWidget *createAvatarWidget();

	const Unit *const unit_;
	DataManager *const dataManager_;

	QProgressBar *hpBar_;
	QProgressBar *psychosisBar_;

signals:
	void select();
	void add();
	void heal();
	void showUnit();
	void showMenu();
};