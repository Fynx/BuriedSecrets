/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class Item;
class ItemWidget;
class Prototype;

class ItemsDisplay : public QWidget {

public:
	static const QSize IconSize;

	ItemsDisplay(DataManager *dataManager);

protected:
	ItemWidget *createItemWidget();
	QListWidget *createItemsList();
	void connectDisplays();

	void setItemsList(const QSet<Item *> &items);
	void setItemsList(const QSet<const Prototype *> &prototypes);

	const Prototype *currentPrototype() const;

	DataManager *const dataManager_;

private:
	ItemWidget *itemWidget_;
	QListWidget *itemsList_;

	QMap<QString, const Prototype *> usedPrototypes_;
	bool inReset_;

private slots:
	void onCurrentChanged(QListWidgetItem *item);
};
