/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/UserInterface.hpp"

#include "General/General.hpp"
#include "Mind/Mind.hpp"
#include "Graphics/GraphicsWidget.hpp"
#include "UserInterface/Viewport/Viewport.hpp"
#include "UserInterface/Menus/MainMenu.hpp"
#include "UserInterface/Game/GameInterface.hpp"
#include "UserInterface/Menus/PostGameMenu.hpp"
#include "UserInterface/Menus/LoadGameMenu.hpp"
#include "UserInterface/Menus/SaveGameMenu.hpp"
#include "UserInterface/Resources.hpp"

UserInterface::UserInterface(General *general, DataManager *dataManager)
	: general_(general),
	  dataManager_(dataManager),
	  mainWindow_(new QMainWindow),
	  gameInterface_(nullptr),
	  postGameMenu_(new PostGameMenu),
	  mainMenu_(new MainMenu(this)),
	  loadGameMenu_(new LoadGameMenu),
	  saveGameMenu_(new SaveGameMenu)
{
	Q_INIT_RESOURCE(resources);

	initMenus();
	initLayout();
	initDevActionsMenu();

	stackedWidget_->setCursor(BSCursor(Cursors::PointerPrimary));
}

UserInterface::~UserInterface()
{
	delete mainWindow_;
}

QMainWindow *UserInterface::getMainWindow()
{
	return mainWindow_;
}

Viewport *UserInterface::getViewport()
{
	return gameInterface_->viewport();
}

bool UserInterface::gameInProgress() const
{
	return (gameInterface_ != nullptr);
}

void UserInterface::newGame(Mind *mind, BoardWidget *boardWidget)
{
	gameInterface_ = new GameInterface(mind, dataManager_, boardWidget);

	connect(gameInterface_, &GameInterface::showMainMenu, this, &UserInterface::onShowMainMenu);
	connect(gameInterface_, &GameInterface::gameEnded, this, &UserInterface::onGameEnded);
	stackedWidget_->insertWidget(static_cast<int>(Menu::Game), gameInterface_);

	switchToMenu(Menu::Game);
	mainMenu_->adjustButtonsVisibility();

	gameInterface_->start();
}

void UserInterface::initMenus()
{
	connect(mainMenu_, &MainMenu::quitActivated, mainWindow_, &QMainWindow::close);
	connect(mainMenu_, &MainMenu::newGameActivated, this, &UserInterface::onNewGame);
	connect(mainMenu_, &MainMenu::continueActivated, this, &UserInterface::onContinueGame);
	connect(mainMenu_, &MainMenu::loadGameActivated, this, &UserInterface::onShowLoadGame);
	connect(mainMenu_, &MainMenu::saveGameActivated, this, &UserInterface::onShowSaveGame);
	connect(postGameMenu_, &PostGameMenu::goToMainMenu, this, &UserInterface::onAfterGame);

	connect(loadGameMenu_, &LoadGameMenu::closeActivated, this, &UserInterface::onShowMainMenu);
	connect(loadGameMenu_, &LoadGameMenu::loadGame, this, &UserInterface::loadGame);
	connect(saveGameMenu_, &SaveGameMenu::closeActivated, this, &UserInterface::onShowMainMenu);
	connect(saveGameMenu_, &SaveGameMenu::saveGame, this, &UserInterface::saveGame);

}

void UserInterface::initLayout()
{
	stackedWidget_ = new QStackedWidget;
	stackedWidget_->insertWidget(static_cast<int>(Menu::MainMenu), mainMenu_);
	stackedWidget_->insertWidget(static_cast<int>(Menu::PostGameMenu), postGameMenu_);
	stackedWidget_->insertWidget(static_cast<int>(Menu::LoadGameMenu), loadGameMenu_);
	stackedWidget_->insertWidget(static_cast<int>(Menu::SaveGameMenu), saveGameMenu_);

	mainWindow_->setCentralWidget(stackedWidget_);
	mainWindow_->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	mainWindow_->setWindowState(Qt::WindowFullScreen);
}

void UserInterface::switchToMenu(Menu menu)
{
	stackedWidget_->setCurrentIndex(static_cast<int>(menu));
}

void UserInterface::clearGame()
{
	if (gameInProgress()) {
		disconnect(gameInterface_, &GameInterface::showMainMenu, this, &UserInterface::onShowMainMenu);
		disconnect(gameInterface_, &GameInterface::gameEnded, this, &UserInterface::onGameEnded);
		stackedWidget_->removeWidget(gameInterface_);
		delete gameInterface_;
		gameInterface_ = nullptr;
	}
}

void UserInterface::initDevActionsMenu()
{
	//DEV TMP
	//these things are not going to be here, so don't worry about menu and qt signals
	QMenu *menuFile = mainWindow_->menuBar()->addMenu("File");

	QAction *actionSaveMap = new QAction("Save level", mainWindow_);
	connect(actionSaveMap, &QAction::triggered, general_, &General::saveLevel);
	menuFile->addAction(actionSaveMap);

	QAction *actionQuit = new QAction("Quit", mainWindow_);
	connect(actionQuit, &QAction::triggered, mainWindow_, &QMainWindow::close);
	actionQuit->setShortcut(Qt::CTRL + Qt::Key_Q);
	menuFile->addAction(actionQuit);

	QMenu *menuDebug = mainWindow_->menuBar()->addMenu("Debug");

	QAction *actionBasePolygonsToggle = new QAction("Toggle base polygons", mainWindow_);
	connect(actionBasePolygonsToggle, &QAction::triggered, general_, &General::toggleDisplayBasePolygons);
	menuDebug->addAction(actionBasePolygonsToggle);

	QAction *actionFOWToggle = new QAction("Toggle Fog of War", mainWindow_);
	connect(actionFOWToggle, &QAction::triggered, general_, &General::toggleDisplayFOW);
	menuDebug->addAction(actionFOWToggle);

	QAction *actionShowPathsToggle = new QAction("Toggle show unit paths", mainWindow_);
	connect(actionShowPathsToggle, &QAction::triggered, general_, &General::toggleShowPaths);
	menuDebug->addAction(actionShowPathsToggle);

	QAction *actionFPSToggle = new QAction("Toggle FPS", mainWindow_);
	connect(actionFPSToggle, &QAction::triggered, general_, &General::toggleDisplayFPS);
	menuDebug->addAction(actionFPSToggle);
}

void UserInterface::onShowMainMenu()
{
	general_->pauseGame();
	switchToMenu(Menu::MainMenu);
}

void UserInterface::onGameEnded(BS::GameState gs)
{
	general_->endGame();
	postGameMenu_->setEnding(gs);
	switchToMenu(Menu::PostGameMenu);
}

void UserInterface::onAfterGame()
{
	mainMenu_->adjustButtonsVisibility();
	switchToMenu(Menu::MainMenu);
}

void UserInterface::onNewGame()
{
	if (gameInProgress())
		general_->endGame();
	general_->startNewGame();
}

void UserInterface::onContinueGame()
{
	general_->resumeGame();
	switchToMenu(Menu::Game);
}

void UserInterface::onShowLoadGame()
{
	general_->pauseGame();
	switchToMenu(Menu::LoadGameMenu);
	loadGameMenu_->refreshList();
}

void UserInterface::onShowSaveGame()
{
	general_->pauseGame();
	switchToMenu(Menu::SaveGameMenu);
	saveGameMenu_->refreshList();
}

void UserInterface::loadGame(QString path)
{
	general_->loadGame(path);
}

void UserInterface::saveGame(QString path)
{
	general_->saveGame(path);
}
