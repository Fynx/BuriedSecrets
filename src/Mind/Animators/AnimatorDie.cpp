/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorDie.hpp"

#include "Mind/Mind.hpp"
#include "GameObjects/Journal.hpp"
#include "GameObjects/Unit.hpp"
#include "DebugManager/DebugManager.hpp"


AnimatorDie::AnimatorDie(Mind *mind) : Animator(mind)
{
	info("AnimatorDie created.");
}


void AnimatorDie::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		if (unit->getHP() <= 0){
			info("Unit dies. Id: " + QString::number(unit->getUid()));
			if (unit->getLocation())
				unit->getLocation()->removeUnit(unit->getUid());
			if (mind->getFactionById(unit->getFactionId())) {
				Journal *journal = mind->getFactionById(unit->getFactionId())->getJournal();
				if (journal != nullptr)
					journal->createEntryDeath(mind, unit);
				mind->getFactionById(unit->getFactionId())->removeUnit(unit->getUid());
			}
			mind->removeObject(unit);
			//delete unit;
		}
	}
}
