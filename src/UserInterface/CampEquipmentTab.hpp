/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "UserInterface/ItemsDisplay.hpp"

class DataManager;
class Equipment;
class Item;
class Mind;

class CampEquipmentTab : public ItemsDisplay {
	Q_OBJECT

public:
	CampEquipmentTab(Equipment *eq, Mind *mind, DataManager *dataManager);

public slots:
	void refresh();

private:
	void initLayout();
	Item *uidToItem(int uid);

	Equipment *eq_;
	Mind *mind_;

private slots:
	void onItemMovedIn(int uid);
	void onItemMovedOut(int uid);
};
