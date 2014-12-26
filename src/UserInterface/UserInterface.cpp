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
	  mainMenuWindow(new MainMenuWindow(interfaceDataManager, general)),
	  gameWindow(new GameWindow(interfaceDataManager, mind, graphicsWidget))
{
	connect(mainMenuWindow, &MainMenuWindow::quit, mainWindow, &QMainWindow::close);
	connect(mainMenuWindow, &MainMenuWindow::switchToGame, this, &UserInterface::switchToGame);
	connect(gameWindow, &GameWindow::switchToMainMenu, this, &UserInterface::switchToMainMenu);

	initLayout();
	devActionsMenu();
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


void UserInterface::initLayout()
{
	stackedWidget = new QStackedWidget;

	stackedWidget->insertWidget(MainMenuWindowIndex, mainMenuWindow);
	stackedWidget->insertWidget(GameWindowIndex, gameWindow);
	stackedWidget->setCurrentIndex(MainMenuWindowIndex);

	mainWindow->setCentralWidget(stackedWidget);
	mainWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	mainWindow->setWindowState(Qt::WindowFullScreen);
}


void UserInterface::switchToGame()
{
	stackedWidget->setCurrentIndex(GameWindowIndex);
}


void UserInterface::switchToMainMenu()
{
	stackedWidget->setCurrentIndex(MainMenuWindowIndex);
}


void UserInterface::devActionsMenu()
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
