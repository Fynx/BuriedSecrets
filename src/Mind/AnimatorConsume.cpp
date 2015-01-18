/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/AnimatorConsume.hpp"

#include <QtCore>

#include "Mind/Mind.hpp"
#include "GameObjects/Faction.hpp"
#include "DebugManager/DebugManager.hpp"


AnimatorConsume::AnimatorConsume(Mind *mind) : Animator(mind)
{
	info("AnimatorConsume created.");
}


void AnimatorConsume::act()
{
	for (Object * obj : objects){
		Faction *faction = dynamic_cast<Faction *>(obj);
		if (!faction)
			continue;

		QSet<int> units = faction->getUnits();
		for (int id : units){
			Unit *unit = dynamic_cast<Unit *>(mind->getObjectFromUid(id));
			if (!unit)
				continue;

			unit->setHP(unit->getHP() - faction->consume(unit->getFoodDemand()));
		}
	}
}
