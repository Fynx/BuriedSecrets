/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorBuildingDmg.hpp"

#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Location.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"

using namespace BS;


AnimatorBuildingDmg::AnimatorBuildingDmg(Mind *mind) : Animator(mind)
{
	info("Animator Building Damage created.");
}


void AnimatorBuildingDmg::act()
{
	for (Object * obj : objects){
		Location *location = dynamic_cast<Location *>(obj);
		if (!location)
			continue;
		float dmg = location->property(TempData::Damage).toFloat();
		if (!dmg)
			continue;

		location->property(TempData::Damage).setValue(0);
		int n = location->getUnitsUids().size();
		if (n == 0)
			continue;
		n = qrand()%n;
		int uid = location->getUnitsUids()[n];
		mind->getObjectFromUid(uid)->property(TempData::Damage).setValue(dmg);
	}
}


