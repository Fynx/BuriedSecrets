/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "CampConstructorTab.hpp"

#include "DataManager/DataManager.hpp"
#include "GameObjects/Equipment.hpp"
#include "Mind/ItemConstructor.hpp"
#include "UserInterface/ItemWidget.hpp"

CampConstructorTab::CampConstructorTab(Equipment *eq, ItemConstructor *ic, DataManager *dm)
	: ItemsDisplay(dm),
	  eq_(eq),
	  itemConstructor_(ic)
{
	initLayout();

// 	TODO setItemsList from itemConstructor_->possibleItems(eq_);
}

void CampConstructorTab::initLayout()
{
	auto layout = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(createItemWidget(), 1);
	layout->addWidget(createItemsList(), 1);
	connectDisplays();
}
