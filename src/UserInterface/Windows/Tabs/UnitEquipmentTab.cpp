/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Windows/Tabs/UnitEquipmentTab.hpp"

#include "Common/Strings.hpp"
#include "DataManager/DataManager.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"
#include "UserInterface/Windows/Tabs/Item/ItemsListWidget.hpp"
#include "UserInterface/Windows/Tabs/Item/ItemWidget.hpp"
#include "UserInterface/Windows/Tabs/Item/SlotWidget.hpp"

UnitEquipmentTab::UnitEquipmentTab(Unit *u, Mind *m, DataManager *dm)
	: dataManager_(dm),
	  unit_(u),
	  mind_(m)
{
	initLayout();
}

void UnitEquipmentTab::initLayout()
{
	auto layout = new QVBoxLayout;
	setLayout(layout);

	itemWidget_ = new ItemWidget(dataManager_);
	layout->addWidget(itemWidget_, 1);
	layout->addLayout(createSlotsLayout(), 1);
}

QLayout *UnitEquipmentTab::createSlotsLayout()
{
	auto formLayout = new QFormLayout;
	formLayout->setLabelAlignment(Qt::AlignRight);

	for (auto &slot : unit_->getEquipment()->getAvailableSlots()) {
		auto sw = new SlotWidget(mind_, slot);
		connect(sw, &SlotWidget::slotActivated, this, &UnitEquipmentTab::showItem);
		connect(sw, &SlotWidget::itemMovedIn, this, &UnitEquipmentTab::onItemMovedIn);
		connect(sw, &SlotWidget::itemMovedOut, this, &UnitEquipmentTab::onItemMovedOut);
		slotWidgets_.insert(slot, sw);
		formLayout->addRow(slotTitle(slot), sw);
	}

	updateSlots();

	return formLayout;
}

QLabel *UnitEquipmentTab::slotTitle(BS::Slot slot)
{
	auto txt = BS::changeSlotToString(slot);
	if (!txt.isEmpty())
		txt[0] = txt[0].toUpper();

	auto slotTitle = new QLabel(txt);
	slotTitle->setFont(QFont("Arial", 16, QFont::Bold));

	return slotTitle;
}

Item *UnitEquipmentTab::uidToItem(int uid)
{
	for (auto item : unit_->getEquipment()->getItems())
		if (item->getUid() == uid)
			return item;

	return nullptr;
}

void UnitEquipmentTab::updateSlots()
{
	for (auto sw : slotWidgets_) {
		auto item = unit_->getEquipment()->getSlotItem(sw->slot());
		if (item != nullptr) {
			QString pictureName = item->getPrototype()->getProperty(Properties::Picture).toString();
			const Resource *res = dataManager_->getResource(pictureName);
			QImage img;
			img.loadFromData(reinterpret_cast<const uchar *>(res->getData()), res->getDataLength());

			sw->setItem(QPixmap::fromImage(img), item->getName(), item->getUid());
		}
		else
			sw->clearItem();
	}
}

void UnitEquipmentTab::showItem(int uid)
{
	auto item = dynamic_cast<Item *>(mind_->getObjectFromUid(uid));
	if (item == nullptr){
		err(QString("Invalid item to be shown, uid: ") + QString::number(uid));
		return;
	}

	itemWidget_->setItem(item);
}

void UnitEquipmentTab::onItemMovedIn(BS::Slot slot, int uid)
{
	auto item = dynamic_cast<Item *>(mind_->getObjectFromUid(uid));
	if (item == nullptr){
		err(QString("Invalid item moved in to slot, uid: ") + QString::number(uid));
		return;
	}

	unit_->getEquipment()->putItemIntoSlot(slot, item);
	unit_->getEquipment()->addItem(item);

	updateSlots();
}

void UnitEquipmentTab::onItemMovedOut(BS::Slot slot, int uid)
{
	auto item = dynamic_cast<Item *>(mind_->getObjectFromUid(uid));
	if (item == nullptr) {
		err(QString("Invalid item moved out from slot, uid: ") + QString::number(uid));
		return;
	}

	unit_->getEquipment()->removeFromSlot(slot);
	unit_->getEquipment()->removeItem(item);

	updateSlots();
}
