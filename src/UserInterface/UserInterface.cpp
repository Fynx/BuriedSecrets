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

	QAction *actionLoadMap = new QAction("Load mind", mainWindow_);
	connect(actionLoadMap, &QAction::triggered, general_, &General::loadMap);
	menuFile->addAction(actionLoadMap);

	QAction *actionSaveMap = new QAction("Save mind", mainWindow_);
	connect(actionSaveMap, &QAction::triggered, general_, &General::saveMap);
	menuFile->addAction(actionSaveMap);

	QAction *actionParseMap = new QAction("Load mind from json", mainWindow_);
	connect(actionParseMap, &QAction::triggered, general_, &General::loadMapFromJson);
	menuFile->addAction(actionParseMap);

	QAction *actionQuit = new QAction("Quit", mainWindow_);
	connect(actionQuit, &QAction::triggered, mainWindow_, &QMainWindow::close);
	menuFile->addAction(actionQuit);
}


void UserInterface::onShowMainMenu()
{
	switchToWindow(Window::MainMenu);
}

void UserInterface::onNewGame()
{
	//first switch to game window to initialize it
	switchToWindow(Window::Game);
	general_->startNewGame();
}

void UserInterface::onContinueGame()
{
	switchToWindow(Window::Game);
}
