/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorBAggressiveAtt.hpp"

#include "Common/Strings.hpp"
#include "Common/Geometry.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"

using namespace BS;


AnimatorBAggressiveAtt::AnimatorBAggressiveAtt(Mind *mind) : Animator(mind)
{
	info("Animator Building Aggressive Attitude created.");
}


void AnimatorBAggressiveAtt::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		if (unit->getAttitude() != Attitude::BuildingAggressive)
			continue;
		if (unit->getState() != State::Inside){
			err("Invalid inside attitude while not in building");
			continue;
		}

		const Object *enemy = unit->getNearestEnemy();
		if (enemy){
			unit->setCommand(Command::Attack);
			unit->setTargetObject(enemy->getUid());
		}
	}
}



