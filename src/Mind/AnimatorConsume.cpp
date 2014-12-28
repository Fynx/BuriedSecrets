/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/AnimatorConsume.hpp"

//TODO use DebugManager instead
#include <QtCore>

#include "Mind/Mind.hpp"
#include "GameObjects/Faction.hpp"

AnimatorConsume::AnimatorConsume(Mind *mind) : Animator(mind)
{
	qDebug() << "AnimatorConsume created.";
}


void AnimatorConsume::act()
{
	for (Object * obj : objects){
		Faction *faction = dynamic_cast<Faction *>(obj);
		if (!faction)
			continue;
		QSet<Unit *> units = faction->getUnits();
		for (Unit *unit : units){
			unit->setHP(unit->getHP() - faction->consume(unit->getFoodDemand()));
		}
	}
}
