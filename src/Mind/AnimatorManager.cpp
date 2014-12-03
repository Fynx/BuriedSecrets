/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/AnimatorManager.hpp"
#include "Mind/AnimatorTest.hpp"

AnimatorManager::AnimatorManager()
{
	animators.append(new AnimatorTest());

	connect(&timer, &QTimer::timeout, this, &AnimatorManager::triggerAnimators);
	timer.start(1000);
}

AnimatorManager::~AnimatorManager()
{
	for (Animator *a : animators)
		delete a;
}

void AnimatorManager::triggerAnimators()
{
	for (Animator *a : animators)
		a->act();
}
