/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "UserInterface/ItemsDisplay.hpp"

class DataManager;
class Equipment;

class CampEquipmentTab : public ItemsDisplay, public QWidget {

public:
	CampEquipmentTab(Equipment *eq, DataManager *dataManager);

private:
	void initLayout();

	Equipment *eq_;
};
