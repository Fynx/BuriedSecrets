/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/GameWindow.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Mind/Mind.hpp"
#include "GameObjects/Unit.hpp"
#include "UserInterface/BoardWidget.hpp"
#include "UserInterface/UnitsPanel.hpp"
#include "UserInterface/FactionPanel.hpp"
#include "UserInterface/CampWindow.hpp"

const int GameWindow::UpdateTimerInterval = 100;

GameWindow::GameWindow(Mind *m, DataManager *dm, BoardWidget *bw, QWidget *parent)
	: QWidget(parent),
	  mind_(m),
	  dataManager_(dm),
	  boardWidget_(bw),
	  updateTimer_(new QTimer),
	  selectionManager_(m, bw),
	  gameWindows_(m, dm),
	  isPaused_(false)
{

	initBoardWidget();
	initUnitsPanel();
	initFactionPanel();

	//WARNING if initialized before boardWidget - goes below
	gameWindows_.initWindows(this);

	connect(&gameWindows_, &GameWindows::pauseGame, this, &GameWindow::pauseGame);
	connect(&gameWindows_, &GameWindows::resumeGame, this, &GameWindow::resumeGame);
	connect(updateTimer_, &QTimer::timeout, this, &GameWindow::refresh);
}

Viewport *GameWindow::viewport()
{
	return selectionManager_.viewport();
}

void GameWindow::startUpdateLoop()
{
	info("Starting UI update loop.");

	update();
	updateTimer_->start(UpdateTimerInterval);
	info("Loop started successfully.");
}

void GameWindow::initBoardWidget()
{
	//Pointer to boardWidget is passed in constructor from Graphics
	boardWidget_->setParent(this);
	connect(boardWidget_, &BoardWidget::selectionEnded, &selectionManager_, &SelectionManager::selectionByRectEnded);
}

void GameWindow::initUnitsPanel()
{
	unitsPanel_ = new UnitsPanel(dataManager_, mind_);
	unitsPanel_->setParent(this);
	connect(unitsPanel_, &UnitsPanel::pickUnit, &selectionManager_, &SelectionManager::pickUnit);
	connect(unitsPanel_, &UnitsPanel::showUnit, &selectionManager_, &SelectionManager::showUnit);
	connect(unitsPanel_, &UnitsPanel::pickUnit, &gameWindows_, &GameWindows::switchUnitWindow);
	connect(unitsPanel_, &UnitsPanel::showUnitMenu, &gameWindows_, &GameWindows::showUnitWindow);
	connect(unitsPanel_, &UnitsPanel::sizeChanged, this, &GameWindow::adjustUnitsPanelGeometry);
}

void GameWindow::initFactionPanel()
{
	factionPanel_ = new FactionPanel;
	factionPanel_->setParent(this);
	connect(factionPanel_, &FactionPanel::campActivated,    &gameWindows_, &GameWindows::showCampWindow);
	connect(factionPanel_, &FactionPanel::journalActivated, &gameWindows_, &GameWindows::showJournalWindow);
}

void GameWindow::refresh()
{
	if (mind_->getGameState() != BS::GameState::Running) {
		updateTimer_->stop();
		emit gameEnded(mind_->getGameState());
		return;
	}

	//TODO move / remove
	if (gameWindows_.campWindow()->knownEquipmentSize() != mind_->getPlayerFaction()->getEquipment()->getItems().count())
		factionPanel_->setCampIconFlash(true);
	else
		factionPanel_->setCampIconFlash(false);

	selectionManager_.refresh();

	unitsPanel_->refresh();
	factionPanel_->refresh(mind_);
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

	//resize unitsPanel
	adjustUnitsPanelGeometry();

	//resize campPanel
	QPoint topLeft(geometry().width() - FactionPanelSize.width(),
	               geometry().height() - FactionPanelSize.height());
	factionPanel_->setGeometry(QRect(topLeft, FactionPanelSize));

	gameWindows_.adjustWindowsGeometry(geometry(), unitsPanel_->sizeHint());

	QWidget::resizeEvent(event);
}

void GameWindow::adjustUnitsPanelGeometry()
{
	QPoint topLeft = QPoint((geometry().width() - unitsPanel_->sizeHint().width()) / 2, 0);
	unitsPanel_->setGeometry(QRect(topLeft, unitsPanel_->sizeHint()));
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
	if (isPaused_ && !gameWindows_.isSubwindowOpen()) {
		mind_->resumeGame();
		isPaused_ = false;
	}
}
