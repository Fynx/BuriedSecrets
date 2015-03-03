/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "CampEquipmentTab.hpp"

#include "DataManager/DataManager.hpp"
#include "GameObjects/Equipment.hpp"
#include "UserInterface/ItemWidget.hpp"

CampEquipmentTab::CampEquipmentTab(Equipment *eq, DataManager *dataManager)
	: ItemsDisplay(dataManager),
	  eq_(eq)
{
	initLayout();

	refresh();
}

void CampEquipmentTab::refresh()
{
	setItemsList(eq_->getItems());
}

void CampEquipmentTab::initLayout()
{
	auto layout = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(createItemWidget(), 1);
	layout->addWidget(createItemsList(), 1);
	connectDisplays();
}
