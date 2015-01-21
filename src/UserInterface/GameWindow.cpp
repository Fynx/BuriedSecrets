/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/GameWindow.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Mind/Mind.hpp"
#include "Common/Strings.hpp"
#include "UserInterface/UnitsPanel.hpp"
#include "UserInterface/CampPanel.hpp"
#include "UserInterface/CampEquipmentWindow.hpp"
#include "UserInterface/JournalWindow.hpp"
#include "UserInterface/UnitWindow.hpp"

const int GameWindow::UpdateTimerInterval = 100;

GameWindow::GameWindow(Mind *mind, QWidget *graphicsWidget, QWidget *parent)
	: QWidget(parent),
	  mind_(mind),
	  gameWidgetManager_(mind_),
	  gameWidget_(graphicsWidget),
	  unitsPanel_(new UnitsPanel),
	  campPanel_(new CampPanel),
	  campEquipmentWindow_(new CampEquipmentWindow),
	  journalWindow_(new JournalWindow),
	  unitWindow_(new UnitWindow(mind_)),
	  updateTimer_(new QTimer)
{
	//TODO order
	gameWidget_->setParent(this);
	campPanel_->setParent(this);
	unitsPanel_->setParent(this);
	campEquipmentWindow_->setParent(this);
	journalWindow_->setParent(this);
	unitWindow_->setParent(this);

	connect(unitsPanel_, &UnitsPanel::sizeChanged, this, &GameWindow::adjustUnitsPanelGeometry);
	connect(unitsPanel_, &UnitsPanel::addUnit,    &gameWidgetManager_, &GameWidgetManager::addUnitToSelectionByUid);
	connect(unitsPanel_, &UnitsPanel::healUnit,   &gameWidgetManager_, &GameWidgetManager::healUnitByUid);
	connect(unitsPanel_, &UnitsPanel::selectUnit, &gameWidgetManager_, &GameWidgetManager::selectUnitByUid);
	connect(unitsPanel_, &UnitsPanel::showUnit,   &gameWidgetManager_, &GameWidgetManager::showUnitByUid);

	//TODO window manager
	connect(unitsPanel_, &UnitsPanel::showUnitMenu, unitWindow_, &UnitWindow::setUnit);
	connect(unitsPanel_, &UnitsPanel::showUnitMenu, unitWindow_, &UnitWindow::show);
	connect(unitsPanel_, &UnitsPanel::showUnitMenu, campEquipmentWindow_, &CampEquipmentWindow::hide);
	connect(unitsPanel_, &UnitsPanel::showUnitMenu, journalWindow_, &JournalWindow::hide);

	connect(campPanel_, &CampPanel::journalActivated, journalWindow_, &JournalWindow::show);
	connect(campPanel_, &CampPanel::journalActivated, campEquipmentWindow_, &CampEquipmentWindow::hide);
	connect(campPanel_, &CampPanel::journalActivated, unitWindow_, &UnitWindow::hide);

	connect(campPanel_, &CampPanel::campEQActivated, campEquipmentWindow_, &CampEquipmentWindow::show);
	connect(campPanel_, &CampPanel::campEQActivated, journalWindow_, &JournalWindow::hide);
	connect(campPanel_, &CampPanel::campEQActivated, unitWindow_, &UnitWindow::hide);


	connect(updateTimer_, &QTimer::timeout, this, &GameWindow::refresh);
}

Viewport * GameWindow::viewport()
{
	return gameWidgetManager_.viewport();
}

void GameWindow::startUpdateLoop()
{
	info("Starting UI update loop.");

	update();
	updateTimer_->start(UpdateTimerInterval);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
		case Qt::Key_Escape:
			emit showMainMenu();
			break;
		default:
			gameWidgetManager_.keyPressEvent(event);
	}
	QWidget::keyPressEvent(event);
}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
	event->button();
	if (childAt(event->pos()) == gameWidget_)
		gameWidgetManager_.mousePressEvent(event);

	QWidget::mousePressEvent(event);
}

void GameWindow::resizeEvent(QResizeEvent *event)
{
	//maximize graphicsWidget_
	gameWidget_->setGeometry(geometry());

	adjustUnitsPanelGeometry();

	//resize campPanel
	QPoint topLeft(geometry().width() - CampPanelSize.width(),
	               geometry().height() - CampPanelSize.height());
	campPanel_->setGeometry(QRect(topLeft, CampPanelSize));

		//set windows geometry
	QPoint windowTopLeft(geometry().width() / 4, unitsPanel_->sizeHint().height());
	QSize windowSize(geometry().width() / 2, geometry().height() - windowTopLeft.y());
	QRect windowRect(windowTopLeft, windowSize);

	campEquipmentWindow_->setGeometry(windowRect);
	journalWindow_->setGeometry(windowRect);
	unitWindow_->setGeometry(windowRect);

	//inform GameWidgetManager about resize (Viewport must know)
	gameWidgetManager_.gameWidgetResized(gameWidget_->size());

	QWidget::resizeEvent(event);
}

void GameWindow::refresh()
{
	unitsPanel_->refresh(mind_);
	campPanel_->refresh(mind_);
}

void GameWindow::adjustUnitsPanelGeometry()
{
	QPoint topLeft = QPoint((geometry().width() - unitsPanel_->sizeHint().width()) / 2, 0);
	unitsPanel_->setGeometry(QRect(topLeft, unitsPanel_->sizeHint()));
}
