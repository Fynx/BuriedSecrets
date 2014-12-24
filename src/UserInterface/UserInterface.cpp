/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/UserInterface.hpp"

#include "General/General.hpp"
#include "UserInterface/IsometricPerspective.hpp"


UserInterface::UserInterface(General *general, Mind *mind, QWidget *graphicsWidget)
	: mainWindow(new QMainWindow()), mainMenuWindow(new MainMenuWindow(mind)),
	  gameWindow(new GameWindow(mind, graphicsWidget)), general(general), mind(mind)
{
	connect(mainMenuWindow, &MainMenuWindow::quit, mainWindow, &QMainWindow::close);
	connect(mainMenuWindow, &MainMenuWindow::switchToGame, this, &UserInterface::switchToGame);
	connect(gameWindow, &GameWindow::switchToMainMenu, this, &UserInterface::switchToMainMenu);

	initLayout();

	//TODO these things are not going to be here, so don't worry about menu and qt signals

	QMenu *menuFile = mainWindow->menuBar()->addMenu("File");

	QAction *actionLoadMap = new QAction(mainWindow);
	actionLoadMap->setText("Load mind");
	connect(actionLoadMap, &QAction::triggered, general, &General::loadMap);
	menuFile->addAction(actionLoadMap);

	QAction *actionSaveMap = new QAction(mainWindow);
	actionSaveMap->setText("Save mind");
	connect(actionSaveMap, &QAction::triggered, general, &General::saveMap);
	menuFile->addAction(actionSaveMap);

	QAction *actionParseMap = new QAction(mainWindow);
	actionParseMap->setText("Create map file");
	connect(actionParseMap, &QAction::triggered, general, &General::createMapFile);
	menuFile->addAction(actionParseMap);

	QAction *actionQuit = new QAction(mainWindow);
	actionQuit->setText("Quit");
	connect(actionQuit, &QAction::triggered, mainWindow, &QMainWindow::close);
	menuFile->addAction(actionQuit);

	const float metreToPxScale = 30.0f;
	// TODO after MapManager is added and there is some map passed to UI, we will need to get the real size here.
	// For now:
	const float mapWidth = 500;
	const float mapHeight = 500;
	viewport = new Viewport(new IsometricPerspective(metreToPxScale));
	viewport->setMapSize(mapWidth, mapHeight);
	viewport->setViewSize(graphicsWidget->width(), graphicsWidget->height());
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


Viewport *UserInterface::getViewport()
{
	return viewport;
}
