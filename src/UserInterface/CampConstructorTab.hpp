/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#pragma once

#include <QtWidgets>
#include "UserInterface/ItemsDisplay.hpp"

class DataManager;
class Equipment;
class ItemConstructor;

class CampConstructorTab : public ItemsDisplay, public QWidget {

public:
	CampConstructorTab(Equipment *eq, ItemConstructor *ic, DataManager *dm);

private:
    void initLayout();

	Equipment *eq_;
	ItemConstructor *itemConstructor_;
};
