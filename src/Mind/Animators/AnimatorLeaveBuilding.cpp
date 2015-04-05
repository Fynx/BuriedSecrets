/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorLeaveBuilding.hpp"

#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "GameObjects/Location.hpp"
#include "Mind/Mind.hpp"

using namespace BS;

AnimatorLeaveBuilding::AnimatorLeaveBuilding(Mind *mind) : Animator(mind)
{
	info("Animator Leave Building created.");
}

void AnimatorLeaveBuilding::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		if (unit->getCommand() != Command::Leave)
			continue;
		Location *building = dynamic_cast<Location *>(unit->getLocation());
		if (!building)
			continue;

		QPointF to(0,0);
		if (building->getExitPoint().isNull())
			to = mind->physicsEngine()->getPosition(building) + building->getOffset();
		else
			to = building->getExitPoint();

		building->removeUnit(unit->getUid());
		if (building->getUnitsUids().size() == 0)
			building->setFactionId(0);

		mind->physicsEngine()->addObject(unit, to);
		unit->setLocation(nullptr);
		unit->setCommand(Command::None);
		unit->setState(State::Idle);
		unit->setAttitude(Attitude::Aggressive);
		unit->setCurrentPath(QList<QPointF>());
	}
}
