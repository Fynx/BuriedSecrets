/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/AnimatorUpdatePath.hpp"

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind.hpp"

using namespace BS;


AnimatorUpdatePath::AnimatorUpdatePath(Mind *mind) : Animator(mind)
{
	info("Animator Update Path created.");
}


void AnimatorUpdatePath::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		Command comm = unit->getCommand();
		QPointF from = mind->physicsEngine()->getPosition(unit);
		QPointF to(0, 0);

		if ((comm == Command::Attack && unit->getState() != State::Attack) || (comm == Command::Heal) || (comm == Command::Enter))
			to = mind->physicsEngine()->getPosition(mind->getObjectFromUid(unit->getTargetObject()));

		if ((comm == Command::Assemble) || (comm == Command::Move))
			to = unit->getTargetPoint();

		if (from.isNull() || to.isNull())
			continue;

		unit->setCurrentPath(mind->getMapManager()->getPath(from, to));
	}
}
