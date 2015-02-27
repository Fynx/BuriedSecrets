/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorWatchTarget.hpp"

#include "Common/Geometry.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"

using namespace BS;


AnimatorWatchTarget::AnimatorWatchTarget(Mind *mind) : Animator(mind)
{
	info("Animator WatchTarget created.");
}


void AnimatorWatchTarget::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		if (unit->getState() != State::Attack && unit->getState() != State::Heal)
			continue;
		Object *target = mind->getObjectFromUid(unit->getTargetObject());
		QVector2D dir(mind->physicsEngine()->getPosition(target) - mind->physicsEngine()->getPosition(unit));
		dir.normalize();
		mind->physicsEngine()->setAngle(unit, Geometry::vecToAngle(dir));
	}
}


