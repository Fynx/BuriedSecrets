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


UserInterface::UserInterface(General *general)
	: general_(general),
	  mainWindow_(new QMainWindow),
	  gameWindow_(nullptr),
	  mainMenuWindow_(new MainMenuWindow(this))
{
	initWindows();
	initLayout();
	initDevActionsMenu();
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
	return (gameWindow_ != nullptr);
}

void UserInterface::newGame(Mind *mind, QWidget *graphicsWidget)
{
	gameWindow_ = new GameWindow(mind, graphicsWidget);

	connect(gameWindow_, &GameWindow::showMainMenu, this, &UserInterface::onShowMainMenu);
	stackedWidget_->insertWidget(static_cast<int>(Window::Game), gameWindow_);

	switchToWindow(Window::Game);
	mainMenuWindow_->adjustButtonsVisibility();

	//TODO
	//Here should be start of GameWindow update loop (not connect)
	connect(actionUILoop_, &QAction::triggered, gameWindow_, &GameWindow::startUpdateLoop);
}

void UserInterface::initWindows()
{
	connect(mainMenuWindow_, &MainMenuWindow::quitActivated, mainWindow_, &QMainWindow::close);
	connect(mainMenuWindow_, &MainMenuWindow::newGameActivated, this, &UserInterface::onNewGame);
	connect(mainMenuWindow_, &MainMenuWindow::continueActivated, this, &UserInterface::onContinueGame);
}

void UserInterface::initLayout()
{
	stackedWidget_ = new QStackedWidget;
	stackedWidget_->insertWidget(static_cast<int>(Window::MainMenu), mainMenuWindow_);

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
		disconnect(actionUILoop_, &QAction::triggered, gameWindow_, &GameWindow::startUpdateLoop);
		disconnect(gameWindow_, &GameWindow::showMainMenu, this, &UserInterface::onShowMainMenu);
		stackedWidget_->removeWidget(gameWindow_);
		delete gameWindow_;
	}
}

void UserInterface::initDevActionsMenu()
{
	//DEV TMP
	//these things are not going to be here, so don't worry about menu and qt signals
	QMenu *menuFile = mainWindow_->menuBar()->addMenu("File");

	QAction *actionLoadMap = new QAction("Load level", mainWindow_);
	connect(actionLoadMap, &QAction::triggered, general_, &General::loadLevel);
	menuFile->addAction(actionLoadMap);

	QAction *actionSaveMap = new QAction("Save level", mainWindow_);
	connect(actionSaveMap, &QAction::triggered, general_, &General::saveLevel);
	menuFile->addAction(actionSaveMap);

	actionUILoop_ = new QAction("Start UI loop", mainWindow_);
	menuFile->addAction(actionUILoop_);

	QAction *actionQuit = new QAction("Quit", mainWindow_);
	connect(actionQuit, &QAction::triggered, mainWindow_, &QMainWindow::close);
	menuFile->addAction(actionQuit);

	QMenu *menuDebug = mainWindow_->menuBar()->addMenu("Debug");

	QAction *actionBasePolygonsToggle = new QAction("Toggle base polygons", mainWindow_);
	connect(actionBasePolygonsToggle, &QAction::triggered, general_, &General::toggleDisplayBasePolygons);
	menuDebug->addAction(actionBasePolygonsToggle);

	QAction *actionFPSToggle = new QAction("Toggle FPS", mainWindow_);
	connect(actionFPSToggle, &QAction::triggered, general_, &General::toggleDisplayFPS);
	menuDebug->addAction(actionFPSToggle);
}

void UserInterface::onShowMainMenu()
{
	switchToWindow(Window::MainMenu);
}

void UserInterface::onNewGame()
{
	general_->startNewGame();
	general_->loadLevel();
}

void UserInterface::onContinueGame()
{
	switchToWindow(Window::Game);
}
