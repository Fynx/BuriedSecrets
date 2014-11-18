#pragma once

#include "PhysicsEngine/PhysicsEngine.h"
#include "SoundsManager/SoundsManager.h"

class Mind {
public:
	Mind(PhysicsEngine *physicsEngine, SoundsManager *soundsManager);

private:
	PhysicsEngine *physicsEngine;
	SoundsManager *soundsManager;
};
