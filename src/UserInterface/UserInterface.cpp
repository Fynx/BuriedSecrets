/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/UserInterface.hpp"


UserInterface::UserInterface(MapManager *mapManager, Mind *mind, QWidget *graphicsWidget)
	: mainWindow(new QMainWindow()), mainMenuWindow(new MainMenuWindow(mind)),
	  gameWindow(new GameWindow(mind, graphicsWidget)), mapManager(mapManager), mind(mind)
{
	connect(mainMenuWindow, &MainMenuWindow::quit, mainWindow, &QMainWindow::close);
	connect(mainMenuWindow, &MainMenuWindow::switchToGame, this, &UserInterface::switchToGame);
	connect(gameWindow, &GameWindow::switchToMainMenu, this, &UserInterface::switchToMainMenu);

	initLayout();

	//TODO these things are not going to be here, so don't worry about menu and qt signals

	QMenu *menuFile = mainWindow->menuBar()->addMenu("File");

	QAction *actionLoadMap = new QAction(mainWindow);
	actionLoadMap->setText("Load mind");
	connect(actionLoadMap, &QAction::triggered, mapManager, &MapManager::loadMap);
	menuFile->addAction(actionLoadMap);

	QAction *actionSaveMap = new QAction(mainWindow);
	actionSaveMap->setText("Save mind");
	connect(actionSaveMap, &QAction::triggered, mapManager, &MapManager::saveMap);
	menuFile->addAction(actionSaveMap);

	QAction *actionQuit = new QAction(mainWindow);
	actionQuit->setText("Quit");
	connect(actionQuit, &QAction::triggered, mainWindow, &QMainWindow::close);
	menuFile->addAction(actionQuit);
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

UserInterface::~UserInterface()
{
	delete mainWindow;
}

QMainWindow *UserInterface::getMainWindow()
{
	return mainWindow;
}
