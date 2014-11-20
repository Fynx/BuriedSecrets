#include "Mind/Mind.hpp"

//TODO use DebugManager instead
#include <QtCore>

Mind::Mind(PhysicsEngine *physicsEngine, SoundsManager *soundsManager)
	: physicsEngine(physicsEngine), soundsManager(soundsManager), animatorManager(new AnimatorManager)
{
	qDebug() << "Mind initialized. Triggering destruction of the world.";
	soundsManager->onEvent(QString("No events for you!"));
}

Mind::~Mind()
{
	delete animatorManager;
}
