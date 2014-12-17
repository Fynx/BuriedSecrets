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
Q_OBJECT;
public:
	General();
	~General();

	QMainWindow *getMainWindow();

	void clear();
	void loadMap();
	void saveMap();
	void createMapFile();

private:
	void initModules();

	//TODO change to pointers
	DataManager   *dataManager;
	DebugManager  *debugManager;
	Graphics      *graphics;
	Mind          *mind;
	PhysicsEngine *physicsEngine;
	SoundsManager *soundsManager;
	UserInterface *userInterface;
};
