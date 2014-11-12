#pragma once

#include "DataManager/DataManager.h"
#include "DebugManager/DebugManager.h"
#include "Graphics/Graphics.h"
#include "Mind/Mind.h"
#include "PhysicsEngine/PhysicsEngine.h"
#include "SoundsManager/SoundsManager.h"
#include "UserInterface/UserInterface.h"

#include <QtWidgets>

//TODO not a QMainWindow most likely, it's in UserInterface, displayed by Graphics
class General : public QMainWindow
{
Q_OBJECT;
public:
	General();

private:
	//TODO change to pointers
	DataManager dataManager;
	DebugManager debugManager;
	Graphics graphics;
	Mind mind;
	PhysicsEngine physicsEngine;
	SoundsManager soundsManager;
	UserInterface userInterface;
};
