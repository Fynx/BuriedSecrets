#include "Mind/Mind.hpp"

//TODO use DebugManager instead
#include <QtCore>

Mind::Mind(PhysicsEngine *physicsEngine, SoundsManager *soundsManager)
	: physicsEngine(physicsEngine), soundsManager(soundsManager), animatorManager(new AnimatorManager)
{
	qDebug() << "Mind initialized. Triggering destruction of the world.";
	soundsManager->onEvent();

	connect(&eventQueueTimer, &QTimer::timeout, this, &Mind::readEvents);
	eventQueueTimer.start(10);
}

Mind::~Mind()
{
	delete animatorManager;
}

void Mind::onEvent(const Event &event)
{
	enqueueEvent(event);
}

void Mind::enqueueEvent(const Event &event)
{
	eventQueueGuard.lock();

	eventQueue.enqueue(event);

	eventQueueGuard.unlock();
}

Event Mind::dequeueEvent()
{
	eventQueueGuard.lock();

	Event event;
	if (eventQueue.isEmpty())
		event = Event();
	else
		event = eventQueue.dequeue();

	eventQueueGuard.unlock();

	return event;
}

void Mind::readEvents()
{
	Event event = dequeueEvent();
	while (!event.toString().isEmpty()) {
		qDebug() << "Event:" << event.toString();
		event = dequeueEvent();
	}
}
