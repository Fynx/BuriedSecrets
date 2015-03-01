/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UnitWindow.hpp"

#include "DebugManager/DebugManager.hpp"
#include "UserInterface/UnitEquipmentTab.hpp"
#include "UserInterface/UnitHistoryTab.hpp"
#include "GameObjects/Unit.hpp"

UnitWindow::UnitWindow(DataManager *dataManager)
	: unit_(nullptr),
	  dataManager_(dataManager)
{
	setAutoFillBackground(true);

	initLayout();
}

void UnitWindow::initLayout()
{
	auto layout  = new QVBoxLayout;
	setLayout(layout);

	title_ = new QLabel;
	title_->setFont(QFont("Times", 18));
	layout->addWidget(title_);

	tabWidget_ = new QTabWidget;
	tabWidget_->tabBar()->setFont(QFont("Times", 16));
	layout->addWidget(tabWidget_);

	closeBtn_ = new QPushButton(tr("Close"));
	closeBtn_->setFont(QFont("Times", 16));
	connect (closeBtn_, &QPushButton::clicked, this, &UnitWindow::exit);
	layout->addWidget(closeBtn_);
}

void UnitWindow::setUnit(Unit *unit)
{
	unit_ = unit;

	title_->setText(unit_->getName());

	int oldIdx = tabWidget_->currentIndex();

	while (tabWidget_->count() > 0) {
		QWidget *widget = tabWidget_->currentWidget();
		tabWidget_->removeTab(tabWidget_->currentIndex());
		delete widget;
	}

	tabWidget_->insertTab(EquipmentIndex, new UnitEquipmentTab(unit_, dataManager_), tr("Equipment"));
	tabWidget_->insertTab(HistoryIndex,   new UnitHistoryTab(unit_, dataManager_),   tr("History"));

	tabWidget_->setCurrentIndex(oldIdx);
}
