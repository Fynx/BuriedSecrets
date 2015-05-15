/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorEnterBuilding.hpp"

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Location.hpp"
#include "GameObjects/Journal.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"

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
		Location *target = mind->getLocation(unit->getTargetObject());
		if (!target)
			continue;

		QPointF from = mind->physicsEngine()->getPosition(unit);
		QPointF to = mind->physicsEngine()->getPosition(target) + target->getOffset();
		if (to.isNull() || from.isNull())
			continue;
		if (QVector2D(to-from).length() > epsilon)
			continue;

		if ((target->getFactionId() != 0) && (target->getFactionId() != unit->getFactionId())){
			unit->setCommand(Command::None);
			continue;
		}

		if (target->isFull()){
			unit->setCommand(Command::None);
			continue;
		}

		target->setFactionId(unit->getFactionId());
		target->insertUnit(unit->getUid());
		unit->setLocation(target);
		mind->physicsEngine()->removeObject(unit);

		Faction *faction = mind->getFactionById(unit->getFactionId());

		// Looting
		QList<Item *> items = target->getItems(unit->getPerception());
		for (Item *it : items) {
			target->removeItem(it);
			faction->getEquipment()->addItem(it);
		}

		if (!items.isEmpty())
			faction->getJournal()->createEntryItemFound(mind, unit, QVector<Item *>::fromList(items));

		// Meeting new units
		Unit *pending = mind->getUnit(target->getUnitMet());
		if (pending){
			target->setUnitMet(0);
			pending->setFactionId(unit->getFactionId());
			faction->addPendingUnit(pending->getUid());
		}

		unit->setAttitude(Attitude::BuildingAggressive);
		unit->setCommand(Command::None);
		unit->setState(State::Inside);
	}
}
