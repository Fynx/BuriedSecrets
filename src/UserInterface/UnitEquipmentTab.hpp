/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class Equipment;
class Item;
class ItemWidget;
class Unit;

class UnitEquipmentTab : public QWidget {

public:
	UnitEquipmentTab(Unit *unit, DataManager *dataManager);

private:
	static const QSize IconSize;

	void initLayout();
	QWidget *createItemsList();
	void initConnections();

	Unit *unit_;
	DataManager *dataManager_;
	Equipment *eq_;

	ItemWidget *itemWidget_;
	QListWidget *itemsList_;
	QMap<int, Item *> itemsUids_; //due to this map Mind is needless

private slots:
	void onItemActivated(QListWidgetItem *item);
};
