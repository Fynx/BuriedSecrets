/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/Windows/UnitWindow.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Mind/Mind.hpp"
#include "UserInterface/Windows/Tabs/UnitEquipmentTab.hpp"
#include "UserInterface/Windows/Tabs/UnitHistoryTab.hpp"
#include "GameObjects/Unit.hpp"

const QFont UnitWindow::LabelFont{"Times", 16};

UnitWindow::UnitWindow(Mind *mind, DataManager *dataManager)
	: unit_(nullptr),
	  mind_(mind),
	  dataManager_(dataManager)
{
	setAutoFillBackground(true);

	initLayout();
}

void UnitWindow::initLayout()
{
	auto layout = new QVBoxLayout;
	setLayout(layout);

	title_ = new QLabel;
	title_->setFont(QFont("Times", 18));
	layout->addWidget(title_);

	tabWidget_ = new QTabWidget;
	tabWidget_->tabBar()->setFont(LabelFont);
	layout->addWidget(tabWidget_, 1);

	buttonsLayout_ = new QStackedLayout;
	buttonsLayout_->insertWidget(ShowMode, createShowButtons());
	buttonsLayout_->insertWidget(DecisionMode, createDecisionButtons());
	layout->addLayout(buttonsLayout_);
}

QWidget *UnitWindow::createShowButtons()
{
	auto closeBtn = new QPushButton(tr("Close"));
	closeBtn->setFont(LabelFont);
	connect(closeBtn, &QPushButton::clicked, this, &UnitWindow::exit);
	return closeBtn;
}

QWidget *UnitWindow::createDecisionButtons()
{
	auto hLayout = new QHBoxLayout;
	auto acceptBtn = new QPushButton(tr("Accept"));
	acceptBtn->setFont(LabelFont);
	connect(acceptBtn, &QPushButton::clicked, this, &UnitWindow::exit);
	connect(acceptBtn, &QPushButton::clicked, this, &UnitWindow::onAccept);
	hLayout->insertWidget(ShowMode, acceptBtn);

	auto declineBtn = new QPushButton(tr("Decline"));
	declineBtn->setFont(LabelFont);
	connect(declineBtn, &QPushButton::clicked, this, &UnitWindow::exit);
	connect(declineBtn, &QPushButton::clicked, this, &UnitWindow::onDecline);
	hLayout->insertWidget(ShowMode, declineBtn);

	auto placeHolder = new QWidget;
	placeHolder->setLayout(hLayout);

	return placeHolder;
}

void UnitWindow::setUnit(Unit *unit)
{
	buttonsLayout_->setCurrentIndex(ShowMode);

	unit_ = unit;

	title_->setText(unit_->getName());

	int oldIdx = tabWidget_->currentIndex();

	while (tabWidget_->count() > 0) {
		QWidget *widget = tabWidget_->currentWidget();
		tabWidget_->removeTab(tabWidget_->currentIndex());
		delete widget;
	}

	tabWidget_->insertTab(EquipmentIndex, new UnitEquipmentTab(unit_, mind_, dataManager_), tr("Equipment"));
	tabWidget_->insertTab(HistoryIndex,   new UnitHistoryTab(unit_, dataManager_),   tr("History"));

	tabWidget_->setCurrentIndex(oldIdx);
}

void UnitWindow::setUnitForDecision(int uid)
{
	auto unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
	if (unit == nullptr) {
		warn(QString("Invalid unit to set for decision, uid: ") + QString::number(uid));
		return;
	}

	setUnit(unit);
	buttonsLayout_->setCurrentIndex(DecisionMode);
}

void UnitWindow::onAccept()
{
	mind_->acceptPendingUnit(unit_->getUid());
}

void UnitWindow::onDecline()
{
	mind_->declinePendingUnit(unit_->getUid());
}
