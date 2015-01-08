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
	info("Clearing game modules...");

	userInterface->clearGame();

	delete graphics;
	delete mind;
	delete physicsEngine;
	delete soundsManager;

	info("done.");
}

void General::startNewGame()
{
	/** Order is the first law of heaven */
	info("New game");

	clearGameModules();

	soundsManager = new SoundsManager;
	physicsEngine = new Box2DEngine;

	//TODO Mind should not have access to dataManager
	mind = new Mind(dataManager, physicsEngine, soundsManager);

	graphics = new Graphics(physicsEngine, dataManager);

	userInterface->newGame(mind, graphics->getGraphicsWidget());
	graphics->startRendering(userInterface->getViewport());
}

void General::loadLevel()
{
	info("Loading level...");
	QJsonObject json = dataManager->loadJsonFromFile("data/maps/map0.json");
	mind->loadFromJson(json);
	graphics->loadMap(mind->getMap());
	info("done.");
}

void General::saveLevel()
{
	info("Saving level...");
	dataManager->saveJsonToFile("data/maps/save0.json", mind->saveToJson());
	info("done.");
}

void General::toggleDisplayBasePolygons()
{
	graphics->toggleShowBasePolygons();
}

void General::toggleDisplayFPS()
{
	graphics->toggleShowFPS();
}
