/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorConsume.hpp"

#include <QtCore>

#include "Mind/Mind.hpp"
#include "GameObjects/Faction.hpp"
#include "GameObjects/Unit.hpp"
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

		QSet<int> units = faction->getUnitsUids();
		for (int id : units){
			Unit *unit = mind->getUnit(id);
			if (!unit)
				continue;

			unit->setHP(unit->getHP() - faction->consume(unit->getFoodDemand()));
		}
	}
}
