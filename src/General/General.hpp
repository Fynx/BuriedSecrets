/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "DataManager/DataManager.hpp"
#include "DebugManager/DebugManager.hpp"
#include "Graphics/Graphics.hpp"
#include "Mind/Mind.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"
#include "SoundsManager/SoundsManager.hpp"
#include "UserInterface/UserInterface.hpp"

#include <QtWidgets>

// General has to be a QObject.
class General: public QObject {
	Q_OBJECT
public:
	General();
	~General();

	QMainWindow *getMainWindow();

	void clearGameModules();
	void startNewGame();

	void saveLevel();

	// FIXME this might need to be moved to DebugManager
	void toggleDisplayBasePolygons();
	void toggleDisplayFPS();

	void pauseGame();
	void resumeGame();

private:
	void initModules();

	//Permanent modules
	DebugManager  *debugManager;
	DataManager   *dataManager;
	UserInterface *userInterface;

	//Per-game modules
	Graphics      *graphics;
	Mind          *mind;
	PhysicsEngine *physicsEngine;
	SoundsManager *soundsManager;
};
