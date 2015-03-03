/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "UserInterface/ItemsDisplay.hpp"

class DataManager;
class Equipment;

class CampEquipmentTab : public ItemsDisplay {
	Q_OBJECT

public:
	CampEquipmentTab(Equipment *eq, DataManager *dataManager);

public slots:
	void refresh();

private:
	void initLayout();

	Equipment *eq_;
};
