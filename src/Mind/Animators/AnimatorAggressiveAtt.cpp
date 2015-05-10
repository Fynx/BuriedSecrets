/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorAggressiveAtt.hpp"

#include "Common/Strings.hpp"
#include "Common/Geometry.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"
#include "Mind/MapManager/MapManager.hpp"

using namespace BS;


AnimatorAggressiveAtt::AnimatorAggressiveAtt(Mind *mind) : Animator(mind)
{
	info("Animator AggressiveAtt created.");
}


void AnimatorAggressiveAtt::act()
{
	for (Object *obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		if (unit->getAttitude() != Attitude::Aggressive)
			continue;
		if (unit->getCommand() != Command::None)
			continue;

		const Object *enemy = unit->getNearestEnemy();
		if (enemy){
			unit->setCommand(Command::Attack);
			unit->setTargetObject(enemy->getUid());
		}
	}
}
