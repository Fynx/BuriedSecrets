/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Windows/Tabs/CampEquipmentTab.hpp"

#include "DataManager/DataManager.hpp"
#include "GameObjects/Equipment.hpp"
#include "Mind/Mind.hpp"
#include "UserInterface/Windows/Tabs/Item/ItemsListWidget.hpp"
#include "UserInterface/Windows/Tabs/Item/ItemWidget.hpp"

CampEquipmentTab::CampEquipmentTab(Equipment *eq, Mind *mind, DataManager *dataManager)
	: ItemsDisplay(dataManager),
	  eq_(eq),
	  mind_(mind)
{
	initLayout();

	refresh();
	connect(this, &ItemsDisplay::itemMovedIn, this, &CampEquipmentTab::onItemMovedIn);
	connect(this, &ItemsDisplay::itemMovedOut, this, &CampEquipmentTab::onItemMovedOut);
}

void CampEquipmentTab::refresh()
{
	setItemsList(eq_->getItems().toList());
}

void CampEquipmentTab::initLayout()
{
	QVBoxLayout *layout = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(createItemWidget(), 1);
	layout->addWidget(createItemsList(), 1);
	connectDisplays();
}

void CampEquipmentTab::onItemMovedIn(int uid)
{
	Item *item = mind_->getItem(uid);
	if (item == nullptr) {
		err(QString("Invalid item moved in to camp, uid: ") + QString::number(uid));
		return;
	}

	eq_->addItem(item);

	refresh();
}

void CampEquipmentTab::onItemMovedOut(int uid)
{
	Item *item = mind_->getItem(uid);
	if (item == nullptr) {
		err(QString("Invalid item moved out from camp, uid: ") + QString::number(uid));
		return;
	}

	eq_->removeItem(item);

	refresh();
}
