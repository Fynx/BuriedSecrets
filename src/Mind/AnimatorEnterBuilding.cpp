/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/AnimatorEnterBuilding.hpp"

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "GameObjects/Building.hpp"
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
		if (unit->getCommand() != Command::EnterBuilding)
			continue;
		Building *target = dynamic_cast<Building *>(mind->getObjectFromUid(unit->getTargetObject()));
		if (!target)
			continue;

		QPointF from = mind->physicsEngine()->getPosition(unit);
		QPointF to = mind->physicsEngine()->getPosition(target);
		if (to.isNull() || from.isNull())
			continue;
		if (QVector2D(to-from).length() > epsilon)
			continue;

		if ((target->getFaction() != 0) && (target->getFaction() != unit->getFaction()))
			continue;

		target->setFaction(unit->getFaction());
		target->insertUnit(unit->getUid());
		unit->setLocation(target);
		mind->physicsEngine()->removeObject(unit);

		// Looting
		QList<Item *> items = target->getItems(unit->getPerception());
		for (Item *it : items){
			target->removeItem(it);
			mind->getFactionById(unit->getFaction())->getEquipment()->addItem(it);
		}

		unit->setCommand(BS::Command::None);
		unit->setState(BS::State::Inside);
	}
}
