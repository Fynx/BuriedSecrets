/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "Common/Enums.hpp"
#include "UserInterface/Windows/Tabs/Item/ItemsDisplay.hpp"

class DataManager;
class Item;
class ItemWidget;
class Mind;
class SlotWidget;
class Unit;

class UnitEquipmentTab : public QWidget {

public:
	UnitEquipmentTab(Unit *u, Mind *m, DataManager *dm);

private:
	void initLayout();
	QLayout *createSlotsLayout();
	QLabel *slotTitle(BS::Slot slot);
	Item *uidToItem(int uid);
	void updateSlots();

	DataManager *const dataManager_;
	Unit *unit_;
	Mind *const mind_;
	QHash<BS::Slot, SlotWidget *> slotWidgets_;
	ItemWidget *itemWidget_;

private slots:
	void showItem(int uid);
	void onItemMovedIn(BS::Slot slot, int uid);
	void onItemMovedOut(BS::Slot slot, int uid);
};
