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

	void onEvent(const Event &event);

private:
	//THREAD SAFE
	void enqueueEvent(const Event &event);
	Event dequeueEvent();
	void readEvents();

	PhysicsEngine *physicsEngine;
	SoundsManager *soundsManager;

	AnimatorManager *animatorManager;

	// Can be like this, can be pointers and virtual inheritance. I prefer this one.
	QQueue <Event> eventQueue;
	QMutex eventQueueGuard;
	QTimer eventQueueTimer;
};
