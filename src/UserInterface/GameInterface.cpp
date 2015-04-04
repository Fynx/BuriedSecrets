/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "UserInterface/GameInterface.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Mind/Mind.hpp"
#include "GameObjects/Unit.hpp"
#include "UserInterface/BoardWidget.hpp"
#include "UserInterface/UnitsPanel.hpp"
#include "UserInterface/FactionPanel.hpp"
#include "UserInterface/CampWindow.hpp"

const int GameInterface::UpdateTimerInterval = 100;

GameInterface::GameInterface(Mind *m, DataManager *dm, BoardWidget *bw, QWidget *parent)
	: QWidget(parent),
	  mind_(m),
	  dataManager_(dm),
	  boardWidget_(bw),
	  updateTimer_(new QTimer),
	  isPaused_(false),
	  gameWindows_(m, dm),
	  gameViewport_(m, bw),
	  gameSelections_(m, gameViewport_),
	  gameCommands_(m, bw, gameViewport_, gameSelections_)
{

	initBoardWidget();
	initUnitsPanel();
	initFactionPanel();

	//WARNING if initialized before boardWidget - goes below
	gameWindows_.initWindows(this);

	connect(&gameWindows_, &GameWindows::pauseGame, this, &GameInterface::pauseGame);
	connect(&gameWindows_, &GameWindows::resumeGame, this, &GameInterface::resumeGame);
	connect(updateTimer_, &QTimer::timeout, this, &GameInterface::refresh);
}

Viewport *GameInterface::viewport()
{
	return gameViewport_.viewport();
}

void GameInterface::startUpdateLoop()
{
	info("Starting UI update loop.");

	update();
	updateTimer_->start(UpdateTimerInterval);
	info("Loop started successfully.");
}

void GameInterface::initBoardWidget()
{
	//Pointer to boardWidget is passed in constructor from Graphics
	boardWidget_->setParent(this);
	connect(boardWidget_, &BoardWidget::selectionEnded, &gameSelections_, &GameSelections::selectionByRectEnded);
}

void GameInterface::initUnitsPanel()
{
	unitsPanel_ = new UnitsPanel(dataManager_, mind_);
	unitsPanel_->setParent(this);
	connect(&gameSelections_, &GameSelections::selectionChanged, unitsPanel_, &UnitsPanel::setSelection);
	connect(unitsPanel_, &UnitsPanel::pickUnit, &gameSelections_, &GameSelections::pickUnit);
	connect(unitsPanel_, &UnitsPanel::showUnit, &gameViewport_, &GameViewport::showUnit);
	connect(unitsPanel_, &UnitsPanel::pickUnit, &gameWindows_, &GameWindows::switchUnitWindow);
	connect(unitsPanel_, &UnitsPanel::showUnitMenu, &gameWindows_, &GameWindows::showUnitWindow);
	connect(unitsPanel_, &UnitsPanel::sizeChanged, this, &GameInterface::adjustUnitsPanelGeometry);
}

void GameInterface::initFactionPanel()
{
	factionPanel_ = new FactionPanel;
	factionPanel_->setParent(this);
	connect(factionPanel_, &FactionPanel::campActivated,    &gameWindows_, &GameWindows::showCampWindow);
	connect(factionPanel_, &FactionPanel::journalActivated, &gameWindows_, &GameWindows::showJournalWindow);
}

void GameInterface::refresh()
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

	gameSelections_.refresh();
	gameCommands_.refresh();

	unitsPanel_->refresh();
	factionPanel_->refresh(mind_);
}

void GameInterface::keyPressEvent(QKeyEvent *event)
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
			gameSelections_.keyPressEvent(event);
			gameViewport_.keyPressEvent(event);
	}
	QWidget::keyPressEvent(event);
}

void GameInterface::mousePressEvent(QMouseEvent *event)
{
	if (childAt(event->pos()) == boardWidget_) {
		gameSelections_.mousePressEvent(event);
		gameCommands_.mousePressEvent(event);
	}

	QWidget::mousePressEvent(event);
}

void GameInterface::resizeEvent(QResizeEvent *event)
{
	//maximize boardWidget_
	boardWidget_->setGeometry(geometry());

	//inform GameViewport about resize
	gameViewport_.gameWidgetResized(boardWidget_->size());

	//resize unitsPanel
	adjustUnitsPanelGeometry();

	//resize campPanel
	QPoint topLeft(geometry().width() - FactionPanelSize.width(),
	               geometry().height() - FactionPanelSize.height());
	factionPanel_->setGeometry(QRect(topLeft, FactionPanelSize));

	gameWindows_.adjustWindowsGeometry(geometry(), unitsPanel_->sizeHint());

	QWidget::resizeEvent(event);
}

void GameInterface::adjustUnitsPanelGeometry()
{
	QPoint topLeft = QPoint((geometry().width() - unitsPanel_->sizeHint().width()) / 2, 0);
	unitsPanel_->setGeometry(QRect(topLeft, unitsPanel_->sizeHint()));
}

void GameInterface::pauseGame()
{
	if (!isPaused_) {
		mind_->pauseGame();
		isPaused_ = true;
	}
}

void GameInterface::resumeGame()
{
	if (isPaused_ && !gameWindows_.isSubwindowOpen()) {
		mind_->resumeGame();
		isPaused_ = false;
	}
}
