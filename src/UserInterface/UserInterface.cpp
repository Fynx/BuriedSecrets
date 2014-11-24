#include "UserInterface/UserInterface.hpp"


UserInterface::UserInterface(MapManager* mapManager, Mind* mind, QWidget* graphicsWidget)
	: mapManager(mapManager), mind(mind), mainWindow(new QMainWindow()), graphicsWidget(graphicsWidget)
{
	//TODO these things are not going to be here, so don't worry about menu and qt signals

	QLabel *l = new QLabel(mainWindow);
	l->setText("BuriedSecrets here. Hello world.");
	mainWindow->setCentralWidget(l);

	QMenu *menuFile = mainWindow->menuBar()->addMenu("File");

	QAction *actionLoadMap = new QAction(mainWindow);
	actionLoadMap->setText("Load map");
	connect(actionLoadMap, &QAction::triggered, mapManager, &MapManager::loadMap);
	menuFile->addAction(actionLoadMap);

	QAction *actionSaveMap = new QAction(mainWindow);
	actionSaveMap->setText("Save map");
	connect(actionSaveMap, &QAction::triggered, mapManager, &MapManager::saveMap);
	menuFile->addAction(actionSaveMap);

	QAction *actionQuit = new QAction(mainWindow);
	actionQuit->setText("Quit");
	connect(actionQuit, &QAction::triggered, mainWindow, &QMainWindow::close);
	menuFile->addAction(actionQuit);

	graphicsWidget->setParent(mainWindow);
	// FIXME Those below are just examples. Soszu, fix this!
	graphicsWidget->resize(150, 50);
	graphicsWidget->move(10, 30);
	graphicsWidget->show();
}

UserInterface::~UserInterface()
{
	delete mainWindow;
}

QMainWindow * UserInterface::getMainWindow()
{
	return mainWindow;
}
