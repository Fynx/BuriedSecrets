#pragma once

#include "Mind/AnimatorManager.h"
#include "PhysicsEngine/PhysicsEngine.h"
#include "SoundsManager/SoundsManager.h"

class Mind {
public:
	Mind(PhysicsEngine *physicsEngine, SoundsManager *soundsManager);
	~Mind();

private:
	PhysicsEngine *physicsEngine;
	SoundsManager *soundsManager;

	AnimatorManager *animatorManager;
};
