/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class ItemWidget;
class Equipment;
class Item;

class CampEquipmentTab : public QWidget {

public:
	CampEquipmentTab(Equipment *eq, DataManager *dataManager);

private:
	static const QSize IconSize;

	void initLayout();
	QWidget *createItemsList();
	void initConnections();

	Equipment *eq_;
	DataManager *const dataManager_;

	ItemWidget *itemWidget_;
	QListWidget *itemsList_;
	QMap<int, Item *> itemsUids_; //due to this map Mind is needless

private slots:
	void onItemActivated(QListWidgetItem *item);
};
