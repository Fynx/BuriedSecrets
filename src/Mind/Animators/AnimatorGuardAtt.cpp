
/* YoLoDevelopment, 2014
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
	info("Animator GuardeAtt created.");
}


void AnimatorGuardAtt::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		if (unit->getAttitude() != Attitude::Guard)
			continue;
		if (unit->getCommand() == Command::Attack && mind->getObjectFromUid(unit->getTargetObject())){
			Object *target = mind->getObjectFromUid(unit->getTargetObject());
			if (mind->getFactionById(unit->getFactionId())->isNeutralFaction(target->getFactionId()))
				unit->setCommand(Command::None);
		}
		if (unit->getCommand() != Command::None)
			continue;
		QPointF from = mind->physicsEngine()->getPosition(unit);
		QPointF to;
		const Object *enemy = nullptr;
		float dist = 10000;
		for (auto *obj: mind->getMapManager()->getVisibleObjects(unit)){
			if (mind->getFactionById(unit->getFactionId())->isNeutralFaction(obj->getFactionId()))
				continue;

			to = mind->physicsEngine()->getPosition(obj);
			if (Geometry::distance(to, from) < dist){
				enemy = obj;
				dist = Geometry::distance(to, from);
			}
		}
		Item *weapon = unit->getEquipment()->getSlotItem(Slot::Weapon);
		if (!weapon){
			err("I has no weapon!");
			continue;
		}
		if (enemy && dist < weapon->getPrototype()->getProperty(Properties::OptimalRange).toFloat()){
			unit->setCommand(Command::Attack);
			unit->setTargetObject(enemy->getUid());
		}
	}
}



