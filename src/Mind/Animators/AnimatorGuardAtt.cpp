/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorGuardAtt.hpp"

#include "Common/Strings.hpp"
#include "Common/Geometry.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"

using namespace BS;


AnimatorGuardAtt::AnimatorGuardAtt(Mind *mind) : Animator(mind)
{
	info("Animator GuardAtt created.");
}


void AnimatorGuardAtt::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		if (unit->getAttitude() != Attitude::Guard)
			continue;
		if (unit->getCommand() != Command::None)
			continue;

		const Object *enemy = unit->getNearestEnemy();
		float dist = unit->property(TempData::NearestDist).toFloat();
		Item *weapon = unit->getEquipment()->getSlotItem(Slot::Weapon);

		if (weapon && enemy && dist < weapon->getPrototype()->getProperty(Properties::OptimalRange).toFloat()){
			unit->setCommand(Command::Attack);
			unit->setTargetObject(enemy->getUid());
		}
	}
}



