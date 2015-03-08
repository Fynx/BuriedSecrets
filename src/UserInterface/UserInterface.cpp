/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/UserInterface.hpp"

#include "General/General.hpp"
#include "Mind/Mind.hpp"
#include "Graphics/GraphicsWidget.hpp"
#include "UserInterface/Viewport.hpp"
#include "UserInterface/MainMenuWindow.hpp"
#include "UserInterface/GameWindow.hpp"
#include "UserInterface/PostGameWindow.hpp"
#include "UserInterface/Resources.hpp"

UserInterface::UserInterface(General *general, DataManager *dataManager)
	: general_(general),
	  dataManager_(dataManager),
	  mainWindow_(new QMainWindow),
	  gameWindow_(nullptr),
	  postGameWindow_(new PostGameWindow),
	  mainMenuWindow_(new MainMenuWindow(this)),
	  gameEnded_(false)
{
	Q_INIT_RESOURCE(UI_data);

	initWindows();
	initLayout();
	initDevActionsMenu();

	stackedWidget_->setCursor(BSCursor(Cursors::PointerPrimary));
}

UserInterface::~UserInterface()
{
	delete mainWindow_;
}

QMainWindow * UserInterface::getMainWindow()
{
	return mainWindow_;
}

Viewport * UserInterface::getViewport()
{
	return gameWindow_->viewport();
}

bool UserInterface::gameInProgress() const
{
	return (gameWindow_ != nullptr) && !gameEnded_;
}

void UserInterface::newGame(Mind *mind, BoardWidget *boardWidget)
{
	gameWindow_ = new GameWindow(mind, dataManager_, boardWidget);
	gameEnded_ = false;

	connect(gameWindow_, &GameWindow::showMainMenu, this, &UserInterface::onShowMainMenu);
	connect(gameWindow_, &GameWindow::gameEnded, this, &UserInterface::onGameEnded);
	stackedWidget_->insertWidget(static_cast<int>(Window::Game), gameWindow_);

	switchToWindow(Window::Game);
	mainMenuWindow_->adjustButtonsVisibility();

	gameWindow_->startUpdateLoop();
}

void UserInterface::initWindows()
{
	connect(mainMenuWindow_, &MainMenuWindow::quitActivated, mainWindow_, &QMainWindow::close);
	connect(mainMenuWindow_, &MainMenuWindow::newGameActivated, this, &UserInterface::onNewGame);
	connect(mainMenuWindow_, &MainMenuWindow::continueActivated, this, &UserInterface::onContinueGame);
	connect(postGameWindow_, &PostGameWindow::goToMainMenu, this, &UserInterface::onAfterGame);
}

void UserInterface::initLayout()
{
	stackedWidget_ = new QStackedWidget;
	stackedWidget_->insertWidget(static_cast<int>(Window::MainMenu), mainMenuWindow_);
	stackedWidget_->insertWidget(static_cast<int>(Window::PostGameMenu), postGameWindow_);

	mainWindow_->setCentralWidget(stackedWidget_);
	mainWindow_->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	mainWindow_->setWindowState(Qt::WindowFullScreen);
}

void UserInterface::switchToWindow(Window window)
{
	stackedWidget_->setCurrentIndex(static_cast<int>(window));
}

void UserInterface::clearGame()
{
	if (gameInProgress()) {
		disconnect(gameWindow_, &GameWindow::showMainMenu, this, &UserInterface::onShowMainMenu);
		disconnect(gameWindow_, &GameWindow::gameEnded, this, &UserInterface::onGameEnded);
		stackedWidget_->removeWidget(gameWindow_);
		delete gameWindow_;
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

	QAction *actionFPSToggle = new QAction("Toggle FPS", mainWindow_);
	connect(actionFPSToggle, &QAction::triggered, general_, &General::toggleDisplayFPS);
	menuDebug->addAction(actionFPSToggle);
}

void UserInterface::onShowMainMenu()
{
	general_->pauseGame();
	switchToWindow(Window::MainMenu);
}

void UserInterface::onGameEnded(BS::GameState gs)
{
	general_->pauseGame();
	postGameWindow_->setEnding(gs);
	switchToWindow(Window::PostGameMenu);
}

void UserInterface::onAfterGame()
{
	gameEnded_ = true;
	mainMenuWindow_->adjustButtonsVisibility();
	switchToWindow(Window::MainMenu);
}

void UserInterface::onNewGame()
{
	general_->startNewGame();
}

void UserInterface::onContinueGame()
{
	general_->resumeGame();
	switchToWindow(Window::Game);
}
