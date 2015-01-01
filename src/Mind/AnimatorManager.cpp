/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "Mind/AnimatorManager.hpp"
#include "Mind/AnimatorTest.hpp"
#include "Mind/AnimatorPhysicsUpdate.hpp"
#include "Mind/AnimationAnimator.hpp"
#include "Mind/AnimatorMove.hpp"
#include "Mind/AnimatorConsume.hpp"
#include "Mind/AnimatorDie.hpp"

AnimatorManager::AnimatorManager(Mind *mind) : signalMapper(this), mind(mind)
{
	initAnimators();
	initTimers();
}

AnimatorManager::~AnimatorManager()
{
	for (Animator *a : animators)
		delete a;
}

void AnimatorManager::initAnimators()
{
	addAnimator(new AnimatorTest(mind), BS::Strings::Animators::Test, 40);
	addAnimator(new AnimatorPhysicsUpdate(mind), BS::Strings::Animators::PhysicsUpdate, 40);
	addAnimator(new AnimationAnimator(mind), BS::Strings::Animators::Animator, 700);
	addAnimator(new AnimatorMove(mind), BS::Strings::Animators::Move, 40);
	addAnimator(new AnimatorConsume(mind), BS::Strings::Animators::Consume, 1000);
	addAnimator(new AnimatorDie(mind), BS::Strings::Animators::Die, 40);
}

void AnimatorManager::initTimers()
{
	for(int msec : intervals.keys()){
		QTimer *t = new QTimer(this);
		timers.append(t);
		signalMapper.setMapping(t, msec);
		connect(t, SIGNAL(timeout()), &signalMapper, SLOT(map()));
		t->start(msec);
	}
	connect(&signalMapper, SIGNAL(mapped(int)), this, SLOT(update(int)));
}

void AnimatorManager::addAnimator(Animator *anim, QString name, int interval)
{
	animators.insert(name, anim);
	intervals[interval].append(anim);
}

bool AnimatorManager::addObject(QString animator, Object *obj)
{
	if (!animators.contains(animator))
		return false;
	if (animators[animator]->hasObject(obj))
		return false;

	animators[animator]->addObject(obj);
	return true;
}

bool AnimatorManager::removeObject(QString animator, Object *obj)
{
	if (!animators.contains(animator))
		return false;
	if (!animators[animator]->hasObject(obj))
		return false;

	animators[animator]->removeObject(obj);
	return true;
}

void AnimatorManager::update(int timeElapsed)
{
	for (Animator *anim : intervals[timeElapsed])
		anim->act();
}
