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
	  mind_(mind),
	  knownEquipmentSize_(0)
{
	initLayout();

	refresh();
	connect(this, &ItemsDisplay::itemMovedIn, this, &CampEquipmentTab::onItemMovedIn);
	connect(this, &ItemsDisplay::itemMovedOut, this, &CampEquipmentTab::onItemMovedOut);
}

void CampEquipmentTab::refresh()
{
	setItemsList(eq_->getItems().toList());
	knownEquipmentSize_ = eq_->getItems().size();
}

int CampEquipmentTab::knownEquipmentSize() const
{
	return knownEquipmentSize_;
}

void CampEquipmentTab::initLayout()
{
	auto layout = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(createItemWidget(), 1);
	layout->addWidget(createItemsList(), 1);
	connectDisplays();
}

Item* CampEquipmentTab::uidToItem(int uid)
{
	for (auto item : eq_->getItems())
		if (item->getUid() == uid)
			return item;

	return nullptr;
}

void CampEquipmentTab::onItemMovedIn(int uid)
{
	auto item = dynamic_cast<Item *>(mind_->getObjectFromUid(uid));
	if (item == nullptr)
		return;
	eq_->addItem(item);

	refresh();
}

void CampEquipmentTab::onItemMovedOut(int uid)
{
	eq_->removeItem(uidToItem(uid));

	refresh();
}