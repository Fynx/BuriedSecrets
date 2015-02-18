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

	info("Done.");
}


void General::startNewGame()
{
	/** Order is the first law of heaven */
	info("Starting new game...");

	clearGameModules();

	soundsManager = new SoundsManager;
	physicsEngine = new Box2DEngine;

	//Initialize & load Mind
	//TODO Mind should not have access to dataManager
	mind = new Mind(dataManager, physicsEngine, soundsManager);
	QJsonObject json = dataManager->loadJsonFromFile("data/maps/map0.json");
	mind->loadFromJson(json);

	//Initialize & load Graphics
	graphics = new Graphics(physicsEngine, dataManager);
	graphics->loadMap(mind->getMap());

	//start UI & Graphics
	//WARNING starting newGame in UI must be after all data is loaded to Mind
	userInterface->newGame(mind, graphics->getGraphicsWidget());
	graphics->startRendering(userInterface->getViewport());

	info("Done.");
}


void General::saveLevel()
{
	info("Saving level...");
	dataManager->saveJsonToFile("data/maps/save0.json", mind->saveToJson());
	info("Done.");
}


void General::toggleDisplayBasePolygons()
{
	graphics->toggleShowBasePolygons();
}


void General::toggleDisplayFPS()
{
	graphics->toggleShowFPS();
}


void General::pauseGame()
{
	mind->pauseGame();
	graphics->pauseRendering();
}


void General::resumeGame()
{
	mind->resumeGame();
	graphics->resumeRendering();
}
