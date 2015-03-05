/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "Common/Enums.hpp"
#include "UserInterface/ItemsDisplay.hpp"

class DataManager;
class Unit;
class Item;
class SlotWidget;

class UnitEquipmentTab : public ItemsDisplay {

public:
	UnitEquipmentTab(Unit *unit, DataManager *dataManager);

private:
	void initLayout();
	QLayout *createSlotsLayout();
	QLabel *slotTitle(BS::Slot slot);
	Item *uidToItem(int uid);

	Unit *unit_;
	QHash<BS::Slot, SlotWidget *> slotWidgets_;

private slots:
	void updateSlots(QVariant itemData);
};
