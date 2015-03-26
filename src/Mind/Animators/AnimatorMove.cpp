/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorMove.hpp"

#include "Mind/Mind.hpp"
#include "GameObjects/Unit.hpp"
#include "DebugManager/DebugManager.hpp"

using namespace BS;

AnimatorMove::AnimatorMove(Mind *mind) : Animator(mind)
{
	info("AnimatorMove created.");
}

void AnimatorMove::act()
{
	for (Object * obj : objects) {
		Unit *unit = dynamic_cast<Unit *>(obj);
		QVector2D dir (0, 0);

		if (!unit)
			continue;

/*		if ( !(obj->getState() == BS::Idle) && !(obj->getState() == BS::Run) && !(obj->getState() == BS::RunAttack))
			continue;*/
		if (unit->getCurrentPath().size() == 0 || obj->getState() == State::Heal || obj->getState() == State::Attack) {
			if (obj->getState() == State::Run){
				obj->setState(State::Idle);
			}
			if (obj->getState() == State::RunBase){
				obj->setState(State::IdleBase);
			}
			mind->physicsEngine()->setVelocity(obj, dir);
			continue;
		}

		dir = QVector2D(unit->getCurrentPath().first() - mind->physicsEngine()->getPosition(obj));

		if (dir.length() < epsilon)
			unit->getCurrentPath().removeFirst();
		else {
			if (obj->getState() == State::Idle)
				obj->setState(State::Run);
			if (obj->getState() == State::IdleBase)
				obj->setState(State::RunBase);
			dir.normalize();
			dir = dir * unit->getSpeed();
			mind->physicsEngine()->setVelocity(obj, dir);
		}
	}
}
