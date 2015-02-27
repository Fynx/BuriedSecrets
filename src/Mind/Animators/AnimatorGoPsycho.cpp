/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorGoPsycho.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Common/Strings.hpp"
#include "GameObjects/Unit.hpp"
#include "GameObjects/Faction.hpp"
#include "Mind/Mind.hpp"

using namespace BS;


AnimatorGoPsycho::AnimatorGoPsycho(Mind *mind) : Animator(mind)
{
	info("AnimatorGoPsycho created.");
}


void AnimatorGoPsycho::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;

		if (unit->property(TempData::NearCamp) == false){
			unit->setPsychosis(unit->getPsychosis() - 1);
		}
		if (unit->getPsychosis() == 0){
			//ToDo - Psychosis effect
		}
	}
}
