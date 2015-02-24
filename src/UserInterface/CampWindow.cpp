/* YoLoDevelopment, 2015
 * All rights reserved.
 */
#include "CampWindow.hpp"

#include "GameObjects/Faction.hpp"
#include "UserInterface/CampEquipmentTab.hpp"
#include "UserInterface/CampConstructorTab.hpp"

CampWindow::CampWindow(Faction *playerFaction, DataManager *dataManager)
	: playerFaction_(playerFaction),
	  dataManager_(dataManager)
{
	setAutoFillBackground(true);

	initLayout();
}

QWidget *CampWindow::createTabWidget()
{
	tabWidget_ = new QTabWidget;
	tabWidget_->tabBar()->setFont(QFont("Times", 16));

	auto equipmentTab = new CampEquipmentTab(playerFaction_->getEquipment(), dataManager_);
	tabWidget_->insertTab(EquipmentIndex, equipmentTab, tr("Equipment"));

	auto constructorTab = new CampConstructorTab;
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
