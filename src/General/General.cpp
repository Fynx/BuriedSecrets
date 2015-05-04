/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "General/General.hpp"

#include "Graphics/GraphicsWidget.hpp"
#include "PhysicsEngine/Box2DEngine.hpp"

General::General()
	: gameStarted_(false),
	  debugManager(new DebugManager),
	  dataManager(new DataManager),
	  userInterface(new UserInterface(this, dataManager)),
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

QMainWindow *General::getMainWindow()
{
	return userInterface->getMainWindow();
}

void General::startNewGame()
{
	info("Starting new game...");
	launchGame("data/maps/map2.json");
	info("Done.");
}

void General::loadGame(const QString &path)
{
	info(QString("Loading game from ") + path);
	launchGame(path);
	info("Done.");
}

void General::saveGame(const QString &path)
{
	info(QString("Saving game in ") + path);
	dataManager->saveJsonToFile(path, mind->saveToJson());
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
	mind->toggleBasePolygons();
}


void General::toggleDisplayFOW()
{
	graphics->toggleFogOfWar();
}


void General::toggleShowPaths()
{
	mind->toggleShowPaths();
}


void General::toggleDisplayFPS()
{
	graphics->toggleShowFPS();
}

void General::pauseGame()
{
	if (!gameStarted_)
		return;

	mind->pauseGame();
	graphics->pauseRendering();
}

void General::resumeGame()
{
	if (!gameStarted_)
		return;

	mind->resumeGame();
	graphics->resumeRendering();
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

void General::launchGame(const QString &path)
{
	gameStarted_ = true;
	clearGameModules();

	soundsManager = new SoundsManager;
	physicsEngine = new Box2DEngine;

	//Initialize & load Mind
	//TODO Mind should not have access to dataManager
	mind = new Mind(dataManager, physicsEngine, soundsManager);
	QJsonObject json = dataManager->loadJsonFromFile(path);
	mind->loadFromJson(json);

	//Initialize & load Graphics
	graphics = new Graphics(physicsEngine, dataManager, mind);
	graphics->loadMap();

	//start UI & Graphics
	//WARNING starting newGame in UI must be after all data is loaded to Mind
	userInterface->newGame(mind, graphics->getGraphicsWidget());
	graphics->startRendering(userInterface->getViewport());

}
