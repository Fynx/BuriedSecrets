/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/AnimatorHeal.hpp"

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"

using namespace BS;


AnimatorHeal::AnimatorHeal(Mind *mind) : Animator(mind)
{
	info("Animator Heal created.");
}


void AnimatorHeal::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		if (unit->getCommand() != Command::Heal)
			continue;
		Unit *target = dynamic_cast<Unit *>(mind->getObjectFromUid(unit->getTargetObject()));
		if (!target)
			continue;

		QPointF from = mind->physicsEngine()->getPosition(unit);
		QPointF to = mind->physicsEngine()->getPosition(target);
		if (to.isNull() || from.isNull())
			continue;
		if (QVector2D(to-from).length() > epsilon)
			continue;
		if (target->getHP() == target->getMaxHP()){
			unit->setCommand(Command::None);
			continue;
		}

		if (unit->getState() != State::Heal){
			unit->setState(State::Heal);
		    target->setHP(target->getHP() + unit->getHealing());
		}
	}
}
