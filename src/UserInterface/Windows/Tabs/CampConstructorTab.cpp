/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Windows/Tabs/CampConstructorTab.hpp"

#include "DataManager/DataManager.hpp"
#include "GameObjects/Equipment.hpp"
#include "Mind/ItemConstructor.hpp"
#include "UserInterface/Windows/Tabs/Item/ItemsListWidget.hpp"
#include "UserInterface/Windows/Tabs/Item/ItemWidget.hpp"

CampConstructorTab::CampConstructorTab(Equipment *eq, ItemConstructor *ic, DataManager *dm)
	: ItemsDisplay(dm),
	  eq_(eq),
	  itemConstructor_(ic)
{
	initLayout();

	disableDragAndDrop();

	connect(this, &CampConstructorTab::itemConstructed, this, &CampConstructorTab::refresh);
	refresh();
}

void CampConstructorTab::refresh()
{
	setItemsList(itemConstructor_->possibleItems(eq_).toList());
}

void CampConstructorTab::initLayout()
{
	auto layout = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(createItemWidget(), 1);
	layout->addWidget(createItemsList(), 1);
	connectDisplays();

	constructBtn_ = new QPushButton(tr("Construct"));
	constructBtn_->setFont(QFont("Times", 20));
	connect(constructBtn_, &QPushButton::clicked, this, &CampConstructorTab::onConstruct);
	layout->addWidget(constructBtn_);
}

void CampConstructorTab::onConstruct()
{
	if (currentPrototype() == nullptr)
		return;

	auto item = itemConstructor_->constructItem(currentPrototype(), eq_);

	refresh();

	emit itemConstructed(item);
}
