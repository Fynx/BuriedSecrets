/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorRegenerate.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Common/Strings.hpp"
#include "GameObjects/Unit.hpp"
#include "GameObjects/Faction.hpp"
#include "Mind/Mind.hpp"

using namespace BS;


AnimatorRegenerate::AnimatorRegenerate(Mind *mind) : Animator(mind)
{
	info("AnimatorRegenerate created.");
}


void AnimatorRegenerate::act()
{
	for (Object * obj : objects){
		Faction *fac = dynamic_cast<Faction *>(obj);
		if (!fac)
			continue;

		for (int id : fac->getUnitsUids()) {
			Unit *unit = dynamic_cast<Unit *>(mind->getObjectFromUid(id));
			if (!unit)
				continue;
			if (unit->property(TempData::NearCamp) == true){
				unit->setPsychosis(unit->getPsychosis() + unit->getRegeneration());
				unit->setHP(unit->getHP() + unit->getRegeneration());
			}
		}
	}
}
