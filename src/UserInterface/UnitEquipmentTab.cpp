/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UnitEquipmentTab.hpp"

#include "DataManager/DataManager.hpp"
#include "GameObjects/Unit.hpp"
#include "UserInterface/ItemWidget.hpp"

UnitEquipmentTab::UnitEquipmentTab(Unit *unit, DataManager *dataManager)
	: ItemsDisplay(dataManager),
	  unit_(unit)
{
	initLayout();

	setItemsList(unit->getEquipment()->getItems().toList());
}

void UnitEquipmentTab::initLayout()
{
	auto layout = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(createItemWidget(), 1);
	layout->addWidget(createItemsList(), 1);
	connectDisplays();
}
