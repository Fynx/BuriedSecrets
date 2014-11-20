#pragma once

#include "Mind/AnimatorManager.hpp"
#include "Mind/Event.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"
#include "SoundsManager/SoundsManager.hpp"

#include <QtCore>

class Mind : public QObject {

Q_OBJECT;
public:
	Mind(PhysicsEngine *physicsEngine, SoundsManager *soundsManager);
	~Mind();

private:
	PhysicsEngine *physicsEngine;
	SoundsManager *soundsManager;

	AnimatorManager *animatorManager;
};
