/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UnitWindow.hpp"

#include "DebugManager/DebugManager.hpp"
#include "UserInterface/UnitEquipmentTab.hpp"
#include "UserInterface/UnitHistoryTab.hpp"
#include "UserInterface/UnitStatsTab.hpp"
#include "GameObjects/Unit.hpp"

UnitWindow::UnitWindow() : unit_(nullptr), tabWidget_(new QTabWidget)
{
	setAutoFillBackground(true);

	title_ = new QLabel;

	closeBtn_ = new QPushButton("Close");
	connect (closeBtn_, &QPushButton::clicked, this, &UnitWindow::exit);

	initLayout();
}

void UnitWindow::initLayout()
{
	QVBoxLayout *layout  = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(title_);
	layout->addWidget(tabWidget_);
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

	tabWidget_->insertTab(EquipmentIndex, new UnitEquipmentTab(unit_), "Equipment");
	tabWidget_->insertTab(HistoryIndex,   new UnitHistoryTab(unit_),   "History");
	tabWidget_->insertTab(StatsIndex,     new UnitStatsTab(unit_),     "Stats");

	tabWidget_->setCurrentIndex(oldIdx);
}
