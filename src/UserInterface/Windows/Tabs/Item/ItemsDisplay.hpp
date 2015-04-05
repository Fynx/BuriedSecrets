/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>

class DataManager;
class Item;
class ItemsListWidget;
class ItemWidget;
class Prototype;

class ItemsDisplay : public QWidget {
	Q_OBJECT

public:
	static const QSize IconSize;

	ItemsDisplay(DataManager *dataManager);

protected:
	ItemWidget *createItemWidget();
	ItemsListWidget *createItemsList();
	void connectDisplays();

	void disableDragAndDrop();

	void setItemsList(const QList<Item *> &items);
	void setItemsList(const QList<const Prototype *> &prototypes);
	void setItemsList(const QList<QPair<const Prototype *, QVariant>> &dataPairs);

	const Prototype *currentPrototype() const;
	QVariant currentData() const;

	DataManager *const dataManager_;

private:
	ItemWidget *itemWidget_;
	ItemsListWidget *itemsList_;

	QMap<QVariant, const Prototype *> usedPrototypes_;
	bool inReset_;

private slots:
	void onCurrentChanged(QListWidgetItem *item);

signals:
	void itemChanged(QVariant data);
	void itemMovedIn(int uid);
	void itemMovedOut(int uid);
};
