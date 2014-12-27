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
#include "UserInterface/InterfaceDataManager.hpp"


UserInterface::UserInterface(const DataManager *dataManager, General *general, Mind *mind, QWidget *graphicsWidget)
	: general(general),
	  mind(mind),
	  interfaceDataManager(new InterfaceDataManager(dataManager)),
	  mainWindow(new QMainWindow()),
	  mainMenuWindow(new MainMenuWindow(interfaceDataManager)),
	  gameWindow(new GameWindow(interfaceDataManager, mind, graphicsWidget))
{
	initWindows();
	initLayout();
	initDevActionsMenu();
}

UserInterface::~UserInterface()
{
	delete mainWindow;
}

QMainWindow * UserInterface::getMainWindow()
{
	return mainWindow;
}

Viewport * UserInterface::getViewport()
{
	return gameWindow->viewport();
}


void UserInterface::initWindows()
{
	connect(mainMenuWindow, &MainMenuWindow::quitActivated, mainWindow, &QMainWindow::close);
	connect(mainMenuWindow, &MainMenuWindow::newGameActivated, this, &UserInterface::onNewGame);
	connect(mainMenuWindow, &MainMenuWindow::continueActivated, this, &UserInterface::onContinueGame);

	connect(gameWindow, &GameWindow::showMainMenu, this, &UserInterface::onShowMainMenu);
}

void UserInterface::initLayout()
{
	stackedWidget = new QStackedWidget;

	stackedWidget->insertWidget(static_cast<int>(Window::MainMenu), mainMenuWindow);
	stackedWidget->insertWidget(static_cast<int>(Window::Game), gameWindow);

	switchToWindow(Window::MainMenu);

	mainWindow->setCentralWidget(stackedWidget);
	mainWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	mainWindow->setWindowState(Qt::WindowFullScreen);
}

void UserInterface::switchToWindow(Window window)
{
	stackedWidget->setCurrentIndex(static_cast<int>(window));
}

void UserInterface::initDevActionsMenu()
{
	//DEV TMP
	//these things are not going to be here, so don't worry about menu and qt signals
	QMenu *menuFile = mainWindow->menuBar()->addMenu("File");

	QAction *actionLoadMap = new QAction("Load mind", mainWindow);
	connect(actionLoadMap, &QAction::triggered, general, &General::loadMap);
	menuFile->addAction(actionLoadMap);

	QAction *actionSaveMap = new QAction("Save mind", mainWindow);
	connect(actionSaveMap, &QAction::triggered, general, &General::saveMap);
	menuFile->addAction(actionSaveMap);

	QAction *actionParseMap = new QAction("Create map file", mainWindow);
	connect(actionParseMap, &QAction::triggered, general, &General::createMapFile);
	menuFile->addAction(actionParseMap);

	QAction *actionQuit = new QAction("Quit", mainWindow);
	connect(actionQuit, &QAction::triggered, mainWindow, &QMainWindow::close);
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
	general->startNewGame();
}

void UserInterface::onContinueGame()
{
	switchToWindow(Window::Game);
}
