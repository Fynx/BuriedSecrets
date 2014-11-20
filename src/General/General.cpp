#include "General/General.hpp"

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
	/** Order is the first law of heaven */

	/** Accesible by everything */
	// we should make it a singleton, really
	debugManager = new DebugManager();

	/** Independent utility modules */

	dataManager = new DataManager();

	soundsManager = new SoundsManager();

	physicsEngine = new PhysicsEngine();

	/** Core modules */

	mind = new Mind(physicsEngine, soundsManager);

	userInterface = new UserInterface(this, mind);

	graphics = new Graphics(mind, userInterface);
}
