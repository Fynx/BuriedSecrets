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
	UnitSection(const Unit *unit, DataManager *dataManager);

	const Unit *unit();
	QSize sizeHint() const;
	void refresh();
	void setSelected(bool isSelected);

private:
	static const QSize AvatarSize;
	static const QSize IconSize;
	static const int BarWidth;

	void mouseDoubleClickEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);

	void initLayout();
	QLayout *createIconsLayout();
	QLayout *createBarsLayout();
	QWidget *createAvatarWidget();

	const Unit *const unit_;
	DataManager *const dataManager_;

	QLabel *locationIcon_;
	QLabel *campIcon_;
// 	QLabel *attitudeIcon_;

	QProgressBar *hpBar_;
	QProgressBar *psychosisBar_;

signals:
	void pickUnit();
	void showUnit();
	void showMenu();
};
