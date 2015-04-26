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

	// FIXME this might need to be moved to DebugManager
	void saveLevel();
	void toggleDisplayBasePolygons();
	void toggleDisplayFOW();
	void toggleShowPaths();
	void toggleDisplayFPS();

public slots:
	void startNewGame();
	void loadGame(const QString &path);
	void saveGame(const QString &path);

	void pauseGame();
	void resumeGame();

private:
	void clearGameModules();
	void launchGame(const QString &path);

	bool gameStarted_;

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
