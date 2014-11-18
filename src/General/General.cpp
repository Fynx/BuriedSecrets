#include "General/General.h"

General::General()
{
	initModules();
}

General::~General()
{
	delete dataManager;
	delete debugManager;
	delete graphics;
	delete mind;
	delete physicsEngine;
	delete soundsManager;
	delete userInterface;
}

QMainWindow * General::getMainWindow()
{
	return userInterface->getMainWindow();
}

void General::loadMap()
{
	qDebug() << "Triggered function loadMap";
	int a;
	dataManager->loadFromFile("blabla", a);
}

void General::saveMap()
{
	qDebug() << "Triggered function saveMap";
	int a = 5;
	dataManager->saveToFile("blabla", a);
}

void General::initModules()
{
	dataManager = new DataManager();

	debugManager = new DebugManager();

	graphics = new Graphics();

	mind = new Mind();

	physicsEngine = new PhysicsEngine();

	soundsManager = new SoundsManager();

	userInterface = new UserInterface(this);
}
