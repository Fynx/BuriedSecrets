/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "General/General.hpp"
#include "PhysicsEngine/Box2DEngine.hpp"


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

void General::startNewGame()
{
	qDebug() << "General seys: \"Starting new game.\"";

	graphics->startRendering(userInterface->getViewport());
}

void General::clear()
{
}

void General::loadMap()
{
	qDebug() << "Triggered function loadMap";
	dataManager->loadFromFile("data/map.bin", *mind);
}

void General::saveMap()
{
	qDebug() << "Triggered function saveMap";
	dataManager->saveToFile("data/map.bin", *mind);
}

void General::createMapFile()
{
	qDebug() << "Triggered function createMapFile";
	mind->insertMap(dataManager->getMap("data/maps/map0.json"));
	saveMap();
	clear();
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

	physicsEngine = new Box2DEngine();

	/** Core modules */

	//TODO Mind should not have access to dataManager
	mind = new Mind(dataManager, physicsEngine, soundsManager);

	graphics = new Graphics(physicsEngine, dataManager);

	userInterface = new UserInterface(dataManager, this, mind, graphics->getGraphicsWidget());
}
