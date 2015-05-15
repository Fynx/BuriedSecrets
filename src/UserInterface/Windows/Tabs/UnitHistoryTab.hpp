/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class Unit;

/**
 * UnitWindow Tab to display units's stats and history.
 */
class UnitHistoryTab : public QWidget {

public:
	UnitHistoryTab(Unit *unit, DataManager *dataManager);

private:
	static const QSize PictureSize;
	static const QMargins ContentsMargins;
	static const int VerticalSpacing = 5;
	static const int HorizontalSpacing = 15;


	void initLayout();
	QWidget *createPictureWidget();
	QLayout *createDataLayout();

	void addProperty(const QString &key, const QString &property, QFormLayout *layout);

	Unit *unit_;
	DataManager *const dataManager_;
};
