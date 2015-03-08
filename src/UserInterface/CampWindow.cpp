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

void CampWindow::refresh()
{
	campEquipmentTab_->refresh();
}

int CampWindow::knownEquipmentSize() const
{
	return campEquipmentTab_->knownEquipmentSize();
}

QWidget *CampWindow::createTabWidget()
{
	tabWidget_ = new QTabWidget;
	tabWidget_->tabBar()->setFont(QFont("Times", 16));

	auto factionEq = mind_->getPlayerFaction()->getEquipment();
	campEquipmentTab_ = new CampEquipmentTab(factionEq, mind_, dataManager_);
	tabWidget_->insertTab(EquipmentIndex, campEquipmentTab_, tr("Equipment"));

	auto constructorTab = new CampConstructorTab(factionEq, mind_->itemConstructor(), dataManager_);
	tabWidget_->insertTab(ConstructorIndex, constructorTab, tr("Constructor"));

	connect(constructorTab, &CampConstructorTab::itemConstructed, campEquipmentTab_, &CampEquipmentTab::refresh);

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
