#include "Mind/Mind.h"

//TODO use DebugManager instead
#include <QtCore>

Mind::Mind(PhysicsEngine *physicsEngine, SoundsManager *soundsManager)
	: physicsEngine(physicsEngine), soundsManager(soundsManager), animatorManager(new AnimatorManager)
{
	qDebug() << "Mind initialized. Triggering destruction of the world.";
	soundsManager->onEvent();
}

Mind::~Mind()
{
	delete animatorManager;
}
