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
	gameWidget_->setParent(this);
	campPanel_->setParent(this);
	unitsPanel_->setParent(this);
	campEquipmentWindow_->setParent(this);
	journalWindow_->setParent(this);
	unitWindow_->setParent(this);

	initUnitsPanel();
	initWindows();

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

void GameWindow::initUnitsPanel()
{
	connect(unitsPanel_, &UnitsPanel::sizeChanged, this, &GameWindow::adjustUnitsPanelGeometry);
	connect(unitsPanel_, &UnitsPanel::addUnit,    &gameWidgetManager_, &GameWidgetManager::addUnitToSelectionByUid);
	connect(unitsPanel_, &UnitsPanel::healUnit,   &gameWidgetManager_, &GameWidgetManager::healUnitByUid);
	connect(unitsPanel_, &UnitsPanel::selectUnit, &gameWidgetManager_, &GameWidgetManager::selectUnitByUid);
	connect(unitsPanel_, &UnitsPanel::showUnit,   &gameWidgetManager_, &GameWidgetManager::showUnitByUid);
}

void GameWindow::initWindows()
{
	connect(campPanel_, &CampPanel::campEQActivated, this, &GameWindow::showCampMenu);
	connect(campPanel_, &CampPanel::journalActivated, this, &GameWindow::showJournal);
	connect(unitsPanel_, &UnitsPanel::showUnitMenu, this, &GameWindow::showUnitMenu);

	connect(campEquipmentWindow_, &CampEquipmentWindow::exit, this, &GameWindow::closeCampMenu);
	connect(journalWindow_, &JournalWindow::exit, this, &GameWindow::closeJournal);
	connect(unitWindow_, &UnitWindow::exit, this, &GameWindow::closeUnitMenu);

	campEquipmentWindow_->hide();
	journalWindow_->hide();
	unitWindow_->hide();
}

void GameWindow::refresh()
{
	unitsPanel_->refresh(mind_);
	campPanel_->refresh(mind_);
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

	//inform GameWidgetManager about resize (Viewport must know)
	gameWidgetManager_.gameWidgetResized(gameWidget_->size());

	adjustUnitsPanelGeometry();

	//resize campPanel
	QPoint topLeft(geometry().width() - CampPanelSize.width(),
	               geometry().height() - CampPanelSize.height());
	campPanel_->setGeometry(QRect(topLeft, CampPanelSize));

	tileCenter(campEquipmentWindow_);
	tileCenter(journalWindow_);
	tileCenter(unitWindow_);

	QWidget::resizeEvent(event);
}

void GameWindow::tileCenter(QWidget *widget)
{
	QPoint topLeft(geometry().width() / 4, unitsPanel_->sizeHint().height());
	QSize size(geometry().width() / 2, geometry().height() - topLeft.y());

	widget->setGeometry(QRect(topLeft, size));
}

void GameWindow::tileLeft(QWidget *widget)
{
	QPoint topLeft(0, unitsPanel_->sizeHint().height());
	QSize size(geometry().width() / 2, geometry().height() - topLeft.y());

	widget->setGeometry(QRect(topLeft, size));
}

void GameWindow::tileRight(QWidget *widget)
{
	QPoint topLeft(geometry().width() / 2, unitsPanel_->sizeHint().height());
	QSize size(geometry().width() / 2, geometry().height() - topLeft.y());

	widget->setGeometry(QRect(topLeft, size));
}

void GameWindow::adjustUnitsPanelGeometry()
{
	QPoint topLeft = QPoint((geometry().width() - unitsPanel_->sizeHint().width()) / 2, 0);
	unitsPanel_->setGeometry(QRect(topLeft, unitsPanel_->sizeHint()));
}

void GameWindow::showCampMenu()
{
	journalWindow_->hide();

	if (unitWindow_->isVisible()) {
		tileRight(unitWindow_);
		tileLeft(campEquipmentWindow_);
	}

	campEquipmentWindow_->show();
}

void GameWindow::showJournal()
{
	campEquipmentWindow_->hide();
	journalWindow_->show();
	unitWindow_->hide();
}

void GameWindow::showUnitMenu(int uid)
{
	unitWindow_->setUnit(uid);

	journalWindow_->hide();

	if (campEquipmentWindow_->isVisible()) {
		tileRight(unitWindow_);
		tileLeft(campEquipmentWindow_);
	}

	unitWindow_->show();
}

void GameWindow::closeCampMenu()
{
	campEquipmentWindow_->hide();
	tileCenter(unitWindow_);
	tileCenter(campEquipmentWindow_);
}

void GameWindow::closeJournal()
{
	journalWindow_->hide();
}

void GameWindow::closeUnitMenu()
{
	unitWindow_->hide();
	tileCenter(unitWindow_);
	tileCenter(campEquipmentWindow_);
}
