/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorHeal.hpp"

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"

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
		if (!target){
			unit->setCommand(Command::None);
			continue;
		}

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
