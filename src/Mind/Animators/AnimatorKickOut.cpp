/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorKickOut.hpp"

#include "Common/Strings.hpp"
#include "Common/Geometry.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"

using namespace BS;


AnimatorKickOut::AnimatorKickOut(Mind *mind) : Animator(mind)
{
	info("Animator KickOut created.");
}


void AnimatorKickOut::act()
{
	for (Object * obj : objects){
		Location *loc = dynamic_cast<Location *>(obj);
		if (!loc)
			continue;

		for (int unitId : loc->getUnitsUids()){
			Unit *unit = dynamic_cast<Unit*> (mind->getObjectFromUid(unitId));
			if (!unit)
				continue;
			unit->setCommand(Command::Leave);
		}
	}
}




