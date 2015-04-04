/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UnitEquipmentTab.hpp"

#include "Common/Strings.hpp"
#include "DataManager/DataManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"
#include "UserInterface/ItemsListWidget.hpp"
#include "UserInterface/ItemWidget.hpp"
#include "UserInterface/SlotWidget.hpp"

UnitEquipmentTab::UnitEquipmentTab(Unit *unit, Mind *mind, DataManager *dataManager)
	: dataManager_(dataManager),
	  unit_(unit),
	  mind_(mind)
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
		auto sw = new SlotWidget(slot);
		connect(sw, &SlotWidget::itemLinkedIn, this, &UnitEquipmentTab::onSlotLinkedIn);
		connect(sw, &SlotWidget::itemLinkedOut, this, &UnitEquipmentTab::onSlotLinkedOut);
		slotWidgets_.insert(slot, sw);
		formLayout->addRow(slotTitle(slot), sw);
	}

	updateSlots();

	return formLayout;
}

QLabel* UnitEquipmentTab::slotTitle(BS::Slot slot)
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

void UnitEquipmentTab::onItemMovedIn(int uid)
{
	auto item = dynamic_cast<Item *>(mind_->getObjectFromUid(uid));
	if (item == nullptr)
		return;
	unit_->getEquipment()->addItem(item);
}

void UnitEquipmentTab::onItemMovedOut(int uid)
{
	unit_->getEquipment()->removeItem(uidToItem(uid));

	updateSlots();
}

void UnitEquipmentTab::onSlotLinkedIn(BS::Slot slot, int uid)
{
	auto item = uidToItem(uid);
	if (!item->getAvailableSlots().contains(slot))
		return;

	unit_->getEquipment()->putItemIntoSlot(slot, item);
	updateSlots();
}

void UnitEquipmentTab::onSlotLinkedOut(BS::Slot slot, int uid)
{
	unit_->getEquipment()->removeFromSlot(slot);
	updateSlots();
}
