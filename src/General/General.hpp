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

//TODO not a QMainWindow most likely, it's in UserInterface, displayed by Graphics
class General : public MapManager {

Q_OBJECT;
public:
	General();
	~General();

	QMainWindow *getMainWindow();

	virtual void loadMap();
	virtual void saveMap();

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
