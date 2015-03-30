/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorUpdatePath.hpp"

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"

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

		if ((comm == Command::Attack && unit->getState() != State::Attack) || (comm == Command::Heal) || (comm == Command::Disassemble))
			to = mind->physicsEngine()->getPosition(mind->getObjectFromUid(unit->getTargetObject()));
		if (comm == Command::Enter){
			Location *target = (Location *)mind->getObjectFromUid(unit->getTargetObject());
			if (!target){
				unit->setCommand(Command::None);
				unit->setState(State::Idle);
				continue;
			}

			to = mind->physicsEngine()->getPosition(target) + target->getOffset();
		}

		if ((comm == Command::Assemble) || (comm == Command::Move))
			to = unit->getTargetPoint();

		if (from.isNull() || to.isNull())
			continue;

		if (comm == Command::Move && QVector2D(from-to).length() < epsilon) {
			if (unit->getState() == State::RunBase || unit->getState() == State::IdleBase)
				unit->setCommand(Command::Base);
			else
				unit->setCommand(Command::None);
			continue;
		}

		unit->setCurrentPath(mind->getMapManager()->getPath(unit, to));
	}
}
