/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/AnimatorDie.hpp"

#include "Mind/Mind.hpp"
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
			mind->removeObject(unit);
		}
	}
}
