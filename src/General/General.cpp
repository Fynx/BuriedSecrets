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


QMainWindow *General::getMainWindow()
{
	return userInterface->getMainWindow();
}


void General::loadMap()
{
	qDebug() << "Triggered function loadMap";
	dataManager->loadFromFile("blabla", *mind);
}


void General::saveMap()
{
	qDebug() << "Triggered function saveMap";
	dataManager->saveToFile("blabla", *mind);
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

	//TODO Mind should not have access to dataManager
	mind = new Mind(dataManager, physicsEngine, soundsManager);

	graphics = new Graphics(mind, dataManager);

	userInterface = new UserInterface(this, mind, graphics->getGraphicsWidget());

	graphics->startRendering();
}
