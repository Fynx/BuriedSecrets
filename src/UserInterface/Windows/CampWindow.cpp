/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "UserInterface/Windows/CampWindow.hpp"

#include "Mind/Mind.hpp"
#include "UserInterface/Windows/Tabs/CampEquipmentTab.hpp"
#include "UserInterface/Windows/Tabs/CampConstructorTab.hpp"
#include "UserInterface/Resources.hpp"
#include "UserInterface/UserInterface.hpp"

CampWindow::CampWindow(Mind *mind, DataManager *dataManager)
	: mind_(mind),
	  dataManager_(dataManager)
{
	setAutoFillBackground(true);

	initLayout();
}

void CampWindow::refresh()
{
	campEquipmentTab_->refresh();
	campConstructorTab_->refresh();
}

QWidget *CampWindow::createTabWidget()
{
	tabWidget_ = new QTabWidget;
	tabWidget_->tabBar()->setFont(QFont("Times", 16));

	auto factionEq = mind_->getPlayerFaction()->getEquipment();
	campEquipmentTab_ = new CampEquipmentTab(factionEq, mind_, dataManager_);
	tabWidget_->insertTab(EquipmentIndex, campEquipmentTab_, tr("Equipment"));

	campConstructorTab_ = new CampConstructorTab(factionEq, mind_->itemConstructor(), dataManager_);
	tabWidget_->insertTab(ConstructorIndex, campConstructorTab_, tr("Constructor"));

	connect(campConstructorTab_, &CampConstructorTab::itemConstructed, campEquipmentTab_, &CampEquipmentTab::refresh);

	return tabWidget_;
}

void CampWindow::initLayout()
{
	QVBoxLayout *layout = new QVBoxLayout;
	setLayout(layout);

	auto title = new QLabel(tr("Camp Equipment"));
	title->setFont(QFont("Times", 18));
	layout->addWidget(title);

	layout->addWidget(createTabWidget());

	closeBtn_ = new QPushButton(tr("Close"));
	closeBtn_->setFont(QFont("Times", 16));
	connect (closeBtn_, &QPushButton::clicked, this, &CampWindow::exit);
	layout->addWidget(closeBtn_);
}
