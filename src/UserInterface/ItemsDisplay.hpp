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
	Q_OBJECT

public:
	static const QSize IconSize;

	ItemsDisplay(DataManager *dataManager);

protected:
	ItemWidget *createItemWidget();
	QListWidget *createItemsList();
	void connectDisplays();

	void setItemsList(const QList<Item *> &items);
	void setItemsList(const QList<const Prototype *> &prototypes);
	void setItemsList(const QList<QPair<const Prototype *, QVariant>> &dataPairs);

	const Prototype *currentPrototype() const;

	DataManager *const dataManager_;

private:
	ItemWidget *itemWidget_;
	QListWidget *itemsList_;

	QMap<QVariant, const Prototype *> usedPrototypes_;
	bool inReset_;

private slots:
	void onCurrentChanged(QListWidgetItem *item);

signals:
	void itemChanged(QVariant data);
};
