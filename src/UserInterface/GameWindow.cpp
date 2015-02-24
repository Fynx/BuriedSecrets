/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/GameWindow.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Mind/Mind.hpp"
#include "Common/Strings.hpp"
#include "UserInterface/BoardWidget.hpp"
#include "UserInterface/UnitsPanel.hpp"
#include "UserInterface/FactionPanel.hpp"
#include "UserInterface/CampWindow.hpp"
#include "UserInterface/JournalWindow.hpp"
#include "UserInterface/UnitWindow.hpp"

const int GameWindow::UpdateTimerInterval = 100;

GameWindow::GameWindow(Mind *mind, DataManager *dataManager, BoardWidget *boardWidget, QWidget *parent)
	: QWidget(parent),
	  mind_(mind),
	  dataManager_(dataManager),
	  boardWidget_(boardWidget),
	  updateTimer_(new QTimer),
	  selectionManager_(mind_),
	  isPaused_(false)
{

	initBoardWidget();
	initUnitsPanel();
	initFactionPanel();

	//WARNING if initialized before boardWidget goes below
	initWindows();

	connect(updateTimer_, &QTimer::timeout, this, &GameWindow::refresh);
}

Viewport * GameWindow::viewport()
{
	return selectionManager_.viewport();
}

void GameWindow::startUpdateLoop()
{
	info("Starting UI update loop.");

	update();
	updateTimer_->start(UpdateTimerInterval);
}

void GameWindow::initWindows()
{
	// CampWindow
	campWindow_ = new CampWindow(mind_->getPlayerFaction(), dataManager_);
	campWindow_->setParent(this);
	campWindow_->hide();
	connect(campWindow_, &CampWindow::exit, this, &GameWindow::closeCampWindow);

	// UnitWindow
	unitWindow_ = new UnitWindow(dataManager_);
	unitWindow_->setParent(this);
	unitWindow_->hide();
	connect(unitWindow_, &UnitWindow::exit, this, &GameWindow::closeUnitWindow);

	// JournalWindow
	journalWindow_ = new JournalWindow;
	journalWindow_->setParent(this);
	journalWindow_->hide();
	connect(journalWindow_, &JournalWindow::exit, this, &GameWindow::closeJournalWindow);
}

void GameWindow::initBoardWidget()
{
	//Pointer to boardWidget is passed in constructor from Graphics
	boardWidget_->setParent(this);
	connect(boardWidget_, &BoardWidget::selectionEnded, &selectionManager_, &SelectionManager::selectionByRectEnded);
}

void GameWindow::initUnitsPanel()
{
	unitsPanel_ = new UnitsPanel(dataManager_);
	unitsPanel_->setParent(this);
	connect(unitsPanel_, &UnitsPanel::addUnit,    &selectionManager_, &SelectionManager::addUnitToSelectionByUid);
	connect(unitsPanel_, &UnitsPanel::healUnit,   &selectionManager_, &SelectionManager::healUnitByUid);
	connect(unitsPanel_, &UnitsPanel::selectUnit, &selectionManager_, &SelectionManager::selectUnitByUid);
	connect(unitsPanel_, &UnitsPanel::showUnit,   &selectionManager_, &SelectionManager::showUnitByUid);
	connect(unitsPanel_, &UnitsPanel::selectUnit, this, &GameWindow::switchUnitWindow);
	connect(unitsPanel_, &UnitsPanel::showUnitMenu, this, &GameWindow::showUnitWindow);
	connect(unitsPanel_, &UnitsPanel::sizeChanged, this, &GameWindow::adjustUnitsPanelGeometry);
}

void GameWindow::initFactionPanel()
{
	factionPanel_ = new FactionPanel;
	factionPanel_->setParent(this);
	connect(factionPanel_, &FactionPanel::campActivated, this, &GameWindow::showCampWindow);
	connect(factionPanel_, &FactionPanel::journalActivated, this, &GameWindow::showJournalWindow);
}

void GameWindow::refresh()
{
	selectionManager_.refresh();

	unitsPanel_->refresh(mind_);
	factionPanel_->refresh(mind_);
}

void GameWindow::pauseGame()
{
	if (!isPaused_) {
		mind_->pauseGame();
		isPaused_ = true;
	}
}

void GameWindow::resumeGame()
{
	if (isPaused_ && !isSubwindowOpen()) {
		mind_->resumeGame();
		isPaused_ = false;
	}
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
		case Qt::Key_Escape:
			emit showMainMenu();
			break;
		case Qt::Key_P:
			if (!isPaused_)
				pauseGame();
			else
				resumeGame();
			break;
		default:
			selectionManager_.keyPressEvent(event);
	}
	QWidget::keyPressEvent(event);
}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
	if (childAt(event->pos()) == boardWidget_)
		selectionManager_.mousePressEvent(event);

	QWidget::mousePressEvent(event);
}

void GameWindow::resizeEvent(QResizeEvent *event)
{
	//maximize boardWidget_
	boardWidget_->setGeometry(geometry());

	//inform GameWidgetManager about resize (Viewport must know)
	selectionManager_.gameWidgetResized(boardWidget_->size());

	adjustUnitsPanelGeometry();

	//resize campPanel
	QPoint topLeft(geometry().width() - FactionPanelSize.width(),
	               geometry().height() - FactionPanelSize.height());
	factionPanel_->setGeometry(QRect(topLeft, FactionPanelSize));

	tileCenter(campWindow_);
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

bool GameWindow::isSubwindowOpen()
{
	return journalWindow_->isVisible() || campWindow_->isVisible() || unitWindow_->isVisible();
}

void GameWindow::showCampWindow()
{
	pauseGame();

	journalWindow_->hide();

	if (unitWindow_->isVisible()) {
		tileRight(unitWindow_);
		tileLeft(campWindow_);
	}

	campWindow_->show();
}

void GameWindow::showJournalWindow()
{
	pauseGame();

	campWindow_->hide();
	journalWindow_->show();
	unitWindow_->hide();
}

void GameWindow::showUnitWindow(int uid)
{
	pauseGame();

	journalWindow_->hide();

	if (campWindow_->isVisible()) {
		tileRight(unitWindow_);
		tileLeft(campWindow_);
	}

	Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
	if (unit == nullptr) {
		err("Invalid unit UID to display");
		return;
	}
	unitWindow_->setUnit(unit);
	unitWindow_->show();
}

void GameWindow::switchUnitWindow(int uid)
{
	Unit *unit = dynamic_cast<Unit *>(mind_->getObjectFromUid(uid));
	if (unit == nullptr) {
		err("Invalid unit UID to display");
		return;
	}

	if (unitWindow_->isVisible())
		unitWindow_->setUnit(unit);

}

void GameWindow::closeCampWindow()
{
	campWindow_->hide();
	tileCenter(unitWindow_);
	tileCenter(campWindow_);

	if (!isSubwindowOpen())
		resumeGame();
}

void GameWindow::closeJournalWindow()
{
	journalWindow_->hide();

	if (!isSubwindowOpen())
		resumeGame();
}

void GameWindow::closeUnitWindow()
{
	unitWindow_->hide();
	tileCenter(unitWindow_);
	tileCenter(campWindow_);

	if (!isSubwindowOpen())
		resumeGame();
}
