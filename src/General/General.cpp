/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "General/General.hpp"
#include "PhysicsEngine/Box2DEngine.hpp"


General::General()
	: debugManager(new DebugManager),
	  dataManager(new DataManager),
	  userInterface(new UserInterface(this)),
	  graphics(nullptr),
	  mind(nullptr),
	  physicsEngine(nullptr),
	  soundsManager(nullptr)
{}

General::~General()
{
	clearGameModules();

	delete userInterface;
	delete dataManager;
	delete debugManager;
}

QMainWindow * General::getMainWindow()
{
	return userInterface->getMainWindow();
}

void General::clearGameModules()
{
	qDebug() << "General seys: \"Clearing game modules.\"";

	userInterface->clearGame();

	delete graphics;
	delete mind;
	delete physicsEngine;
	delete soundsManager;
}

void General::startNewGame()
{
	/** Order is the first law of heaven */
	qDebug() << "General seys: \"Starting new game.\"";

	clearGameModules();

	soundsManager = new SoundsManager;
	physicsEngine = new Box2DEngine;

	//TODO Mind should not have access to dataManager
	mind = new Mind(dataManager, physicsEngine, soundsManager);

	graphics = new Graphics(physicsEngine, dataManager);

	userInterface->newGame(mind, graphics->getGraphicsWidget());
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
