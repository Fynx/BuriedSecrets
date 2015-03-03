/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class Item;
class ItemWidget;

class ItemsDisplay : public QObject {

public:
	static const QSize IconSize;

	ItemsDisplay(DataManager *dataManager);

protected:
	ItemWidget *createItemWidget();
	QListWidget *createItemsList();
	void connectDisplays();

	void setItemsList(QSet<Item *> items);

	DataManager *const dataManager_;

private:
	ItemWidget *itemWidget_;
	QListWidget *itemsList_;

	QMap<int, Item *> itemsUids_; //due to this map Mind is needless

private slots:
	void onItemActivated(QListWidgetItem *item);
};
