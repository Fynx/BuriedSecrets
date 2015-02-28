/* YoLoDevelopment, 2014
 * All rights reserved.
 */

#include "Mind/Animators/AnimatorMobAttitude.hpp"

#include "Common/Strings.hpp"
#include "Common/Geometry.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Mind.hpp"

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
		if (enemy){
			unit->setCommand(Command::Attack);
			unit->setTargetObject(enemy->getUid());
			continue;
		}

		if (unit->getCurrentPath().size() == 0){
			unit->setCommand(Command::Move);
			QSizeF limit = mind->getMapManager()->getMap()->getSize();
			to = QPointF(qrand() % (int)limit.width(), qrand() % (int)limit.height());
			unit->setCurrentPath(mind->getMapManager()->getPath(from, to));
		}
	}
}


