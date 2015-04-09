/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorMobAttitude.hpp"

#include "Common/Strings.hpp"
#include "Common/Geometry.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"
#include "Mind/MapManager/MapManager.hpp"

using namespace BS;


AnimatorMobAttitude::AnimatorMobAttitude(Mind *mind) : Animator(mind)
{
	info("Animator MobAttitude created.");
}


void AnimatorMobAttitude::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		if (unit->getCommand() != Command::None && unit->getCommand() != Command::Move)
			continue;

		const Object *enemy = unit->getNearestEnemy();
		if (enemy){
			unit->setCommand(Command::Attack);
			unit->setTargetObject(enemy->getUid());
			continue;
		}

		if (unit->getCurrentPath().size() == 0){
			unit->setCommand(Command::Move);
			unit->setCurrentPath(unit->getPatrolRoute().toList());
		}
	}
}


