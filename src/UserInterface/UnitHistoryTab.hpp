/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class Unit;

class UnitHistoryTab : public QWidget {

public:
	UnitHistoryTab(Unit *unit, DataManager *dataManager);

private:
	static const QSize PictureSize;
	static const QMargins ContentsMargins;

	void initLayout();
	QWidget *createPictureWidget();
	QLayout *createDataLayout();

	QLabel *keyLabel(const QString &title);
	QLabel *valueLabel(const QString &value);

	Unit *unit_;
	DataManager *const dataManager_;
};
