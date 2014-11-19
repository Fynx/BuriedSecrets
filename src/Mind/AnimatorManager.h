#pragma once

#include "Mind/Animator.h"

#include <QtCore>

class AnimatorManager : public QObject {

Q_OBJECT;
public:
	AnimatorManager();
	~AnimatorManager();

private:
	void triggerAnimators();

	//TODO separate event animators from the ones triggered by the timeout
	QVector <Animator *> animators;

	QTimer timer;
};