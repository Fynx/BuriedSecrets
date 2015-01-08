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
	qDebug() << "General says: \"Clearing game modules.\"";

	userInterface->clearGame();

	delete graphics;
	delete mind;
	delete physicsEngine;
	delete soundsManager;
}

void General::startNewGame()
{
	/** Order is the first law of heaven */
	qDebug() << "General says: \"Starting new game.\"";

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
	qDebug() << "LoadLevel";
	QJsonObject json = dataManager->loadJsonFromFile("data/maps/map0.json");
	mind->loadFromJson(json);
	graphics->loadMap(mind->getMap());
}

void General::saveLevel()
{
	qDebug() << "SaveLevel";
	dataManager->saveJsonToFile("data/maps/save0.json", mind->saveToJson());
}

void General::toggleDisplayBasePolygons()
{
	graphics->toggleShowBasePolygons();
}

void General::toggleDisplayFPS()
{
	graphics->toggleShowFPS();
}
