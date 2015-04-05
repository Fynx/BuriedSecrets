/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "UserInterface/Windows/Tabs/Item/ItemsDisplay.hpp"

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
	int knownEquipmentSize() const;

private:
	void initLayout();

	Equipment *eq_;
	Mind *mind_;
	int knownEquipmentSize_;

private slots:
	void onItemMovedIn(int uid);
	void onItemMovedOut(int uid);
};
