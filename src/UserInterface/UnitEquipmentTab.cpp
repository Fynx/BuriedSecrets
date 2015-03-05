/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UnitEquipmentTab.hpp"

#include "Common/Strings.hpp"
#include "DataManager/DataManager.hpp"
#include "GameObjects/Unit.hpp"
#include "UserInterface/ItemWidget.hpp"
#include "UserInterface/SlotWidget.hpp"

UnitEquipmentTab::UnitEquipmentTab(Unit *unit, DataManager *dataManager)
	: ItemsDisplay(dataManager),
	  unit_(unit)
{
	initLayout();

	connect(this, &ItemsDisplay::itemChanged, this, &UnitEquipmentTab::updateSlots);
	connect(this, &ItemsDisplay::itemChanged, this, &UnitEquipmentTab::updateSlots);

	setItemsList(unit->getEquipment()->getItems().toList());
}

void UnitEquipmentTab::initLayout()
{
	auto layout = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(createItemWidget(), 1);

	auto hLayout = new QHBoxLayout;
	layout->addLayout(hLayout, 1);

	hLayout->addWidget(createItemsList(), 1);
	hLayout->addLayout(createSlotsLayout(), 1);

	connectDisplays();
}

QLayout *UnitEquipmentTab::createSlotsLayout()
{
	QList<BS::Slot> displayedSlots_ {
		BS::Slot::Weapon, BS::Slot::Armor, BS::Slot::Medicament, BS::Slot::Tool,
		BS::Slot::Fortification, BS::Slot::Perception,
	};

	auto formLayout = new QFormLayout;
	formLayout->setLabelAlignment(Qt::AlignRight);

	for (auto slot : displayedSlots_) {
		auto sw = new SlotWidget(slot);
		slotWidgets_.insert(slot, sw);
		formLayout->addRow(slotTitle(slot), sw);

		auto item = unit_->getEquipment()->getSlotItem(slot);
		if (item != nullptr) {
			QString pictureName = item->getPrototype()->getProperty(Properties::Picture).toString();
			const Resource *res = dataManager_->getResource(pictureName);
			QImage img;
			img.loadFromData(reinterpret_cast<const uchar *>(res->getData()), res->getDataLength());

			sw->setItem(QPixmap::fromImage(img), item->getName(), item->getUid());
		}
	}

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

void UnitEquipmentTab::updateSlots(QVariant itemData)
{
	for (auto sw : slotWidgets_) {
		sw->markEnabled(false);
		sw->markLinked(false);
	}

	auto item = uidToItem(itemData.toInt());
	if (item == nullptr)
		return;

	for (auto sw : slotWidgets_) {
		sw->markEnabled(item->isSlotAvailable(sw->slot()));
		sw->markLinked(sw->itemUid() == item->getUid());
	}
}
