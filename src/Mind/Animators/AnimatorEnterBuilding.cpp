/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorEnterBuilding.hpp"

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "GameObjects/Location.hpp"
#include "Mind/Mind.hpp"

using namespace BS;


AnimatorEnterBuilding::AnimatorEnterBuilding(Mind *mind) : Animator(mind)
{
	info("Animator Enter Building created.");
}


void AnimatorEnterBuilding::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		if (unit->getCommand() != Command::Enter)
			continue;
		Location *target = dynamic_cast<Location *>(mind->getObjectFromUid(unit->getTargetObject()));
		if (!target)
			continue;

		QPointF from = mind->physicsEngine()->getPosition(unit);
		QPointF to = mind->physicsEngine()->getPosition(target);
		if (to.isNull() || from.isNull())
			continue;
		if (QVector2D(to-from).length() > epsilon)
			continue;

		if ((target->getFactionId() != 0) && (target->getFactionId() != unit->getFactionId())){
			unit->setCommand(Command::None);
			continue;
		}

		if (target->getCapacity() <= target->getUnitsUids().size()){
			unit->setCommand(Command::None);
			continue;
		}

		target->setFactionId(unit->getFactionId());
		target->insertUnit(unit->getUid());
		unit->setLocation(target);
		mind->physicsEngine()->removeObject(unit);

		// Looting
		QList<Item *> items = target->getItems(unit->getPerception());
		for (Item *it : items){
			target->removeItem(it);
			mind->getFactionById(unit->getFactionId())->getEquipment()->addItem(it);
		}

		unit->setAttitude(Attitude::BuildingAggressive);
		unit->setCommand(Command::None);
		unit->setState(State::Inside);
	}
}
