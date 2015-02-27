/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorMove.hpp"

#include "Mind/Mind.hpp"
#include "GameObjects/Unit.hpp"
#include "DebugManager/DebugManager.hpp"


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

		if (unit->getCurrentPath().size() == 0 || obj->getState() == BS::Heal || obj->getState() == BS::Attack) {
			if (obj->getState() == BS::Run){
				obj->setState(BS::Idle);
			}
			mind->physicsEngine()->setVelocity(obj, dir);
			continue;
		}

		dir = QVector2D(unit->getCurrentPath().first() - mind->physicsEngine()->getPosition(obj));

		if (dir.length() < epsilon)
			unit->getCurrentPath().removeFirst();
		else {
			if (obj->getState() == BS::Idle)
				obj->setState(BS::Run);
			dir.normalize();
			dir = dir * unit->getSpeed();
			mind->physicsEngine()->setVelocity(obj, dir);
		}
	}
}
