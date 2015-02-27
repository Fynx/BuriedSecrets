/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "Mind/Animators/AnimatorManager.hpp"
#include "Mind/Animators/AnimatorTest.hpp"
#include "Mind/Animators/AnimatorPhysicsUpdate.hpp"
#include "Mind/Animators/AnimationAnimator.hpp"
#include "Mind/Animators/AnimatorMove.hpp"
#include "Mind/Animators/AnimatorConsume.hpp"
#include "Mind/Animators/AnimatorDie.hpp"
#include "Mind/Animators/AnimatorUpdatePath.hpp"
#include "Mind/Animators/AnimatorRegenerate.hpp"
#include "Mind/Animators/AnimatorGoPsycho.hpp"
#include "Mind/Animators/AnimatorHeal.hpp"
#include "Mind/Animators/AnimatorAssemble.hpp"
#include "Mind/Animators/AnimatorEnterBuilding.hpp"
#include "Mind/Animators/AnimatorLeaveBuilding.hpp"
#include "Mind/Animators/AnimatorWeapon.hpp"
#include "Mind/Animators/AnimatorAttack.hpp"
#include "Mind/Animators/AnimatorUpdateFOV.hpp"
#include "Mind/Animators/AnimatorApplyDamage.hpp"
#include "Mind/Animators/AnimatorNearCamp.hpp"
#include "Mind/Animators/AnimatorWatchTarget.hpp"


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
	info("Initializing animators...");
	addAnimator(new AnimatorTest(mind), Animators::Test, 40);
	addAnimator(new AnimatorPhysicsUpdate(mind), Animators::PhysicsUpdate, 40);
	addAnimator(new AnimationAnimator(mind), Animators::Animation, 700);
	addAnimator(new AnimatorMove(mind), Animators::Move, 40);
	addAnimator(new AnimatorConsume(mind), Animators::Consume, 1000);
	addAnimator(new AnimatorApplyDamage(mind), Animators::ApplyDamage, 40);
	addAnimator(new AnimatorDie(mind), Animators::Die, 40);
	addAnimator(new AnimatorUpdatePath(mind), Animators::UpdatePath, 100);
	addAnimator(new AnimatorRegenerate(mind), Animators::Regenerate, 1000);
	addAnimator(new AnimatorGoPsycho(mind), Animators::GoPsycho, 1000);
	addAnimator(new AnimatorHeal(mind), Animators::Heal, 100);
	addAnimator(new AnimatorAssemble(mind), Animators::Assemble, 100);
	addAnimator(new AnimatorEnterBuilding(mind), Animators::EnterBuilding, 100);
	addAnimator(new AnimatorLeaveBuilding(mind), Animators::LeaveBuilding, 100);
	addAnimator(new AnimatorWeapon(mind), Animators::Weapon, 100);
	addAnimator(new AnimatorAttack(mind), Animators::Attack, 100);
	addAnimator(new AnimatorUpdateFOV(mind), Animators::UpdateFOV, 50);
	addAnimator(new AnimatorNearCamp(mind), Animators::NearCamp, 1000);
	addAnimator(new AnimatorWatchTarget(mind), Animators::WatchTarget, 40);
	info("done.");
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


void AnimatorManager::pauseGame()
{
	for (QTimer *t : timers)
		if (t->isActive())
			t->stop();
}


void AnimatorManager::resumeGame()
{
	for (QTimer *t : timers)
		if (!t->isActive())
			t->start();
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


bool AnimatorManager::removeObject(Object *obj)
{
	for(QString anim : getAnimatorsForObject(obj))
		removeObject(anim, obj);
	return true;
}


QVector<QString> AnimatorManager::getAnimatorsForObject(const Object *obj) const
{
	QVector<QString> result;
	for (QMap<QString, Animator *>::ConstIterator it = animators.cbegin(); it != animators.cend(); ++it)
		if (it.value()->hasObject(obj))
			result.append(it.key());
	return result;
}


void AnimatorManager::update(int timeElapsed)
{
	for (Animator *anim : intervals[timeElapsed])
		anim->act();
}
