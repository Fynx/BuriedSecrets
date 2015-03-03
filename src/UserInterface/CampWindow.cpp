/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "CampWindow.hpp"

#include "Mind/Mind.hpp"
#include "UserInterface/CampEquipmentTab.hpp"
#include "UserInterface/CampConstructorTab.hpp"
#include "UserInterface/Resources.hpp"
#include "UserInterface/UserInterface.hpp"

CampWindow::CampWindow(Mind *mind, DataManager *dataManager)
	: mind_(mind),
	  dataManager_(dataManager)
{
	setAutoFillBackground(true);

	initLayout();
}

QWidget *CampWindow::createTabWidget()
{
	tabWidget_ = new QTabWidget;
	tabWidget_->tabBar()->setFont(QFont("Times", 16));

	auto factionEq = mind_->getPlayerFaction()->getEquipment();
	auto equipmentTab = new CampEquipmentTab(factionEq, dataManager_);
	tabWidget_->insertTab(EquipmentIndex, equipmentTab, tr("Equipment"));

	auto constructorTab = new CampConstructorTab(factionEq, mind_->itemConstructor(), dataManager_);
	tabWidget_->insertTab(ConstructorIndex, constructorTab, tr("Constructor"));

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
