/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "UserInterface/ItemsDisplay.hpp"

class DataManager;
class Equipment;
class Item;
class ItemConstructor;

class CampConstructorTab : public ItemsDisplay {
	Q_OBJECT

public:
	CampConstructorTab(Equipment *eq, ItemConstructor *ic, DataManager *dm);

public slots:
	void refresh();

private:
    void initLayout();

	Equipment *eq_;
	ItemConstructor *itemConstructor_;

	QPushButton *constructBtn_;

private slots:
	void onConstruct();

signals:
	void itemConstructed(const Item *item);
};
