/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animator.hpp"

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