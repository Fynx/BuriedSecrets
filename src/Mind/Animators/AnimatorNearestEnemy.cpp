/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorNearestEnemy.hpp"

#include "Common/Geometry.hpp"
#include "Common/Strings.hpp"
#include "DebugManager/DebugManager.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/MapManager/MapManager.hpp"
#include "Mind/Mind.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"

using namespace BS;


AnimatorNearestEnemy::AnimatorNearestEnemy(Mind *mind) : Animator(mind)
{
	info("Animator NearestEnemy created.");
}


void AnimatorNearestEnemy::act()
{
	for (Object * obj : objects){
		Unit *unit = dynamic_cast<Unit *>(obj);
		if (!unit)
			continue;
		QPointF from;
		if (unit->getState() == State::Inside)
			from = mind->physicsEngine()->getPosition(unit->getLocation());
		else
			from = mind->physicsEngine()->getPosition(unit);

		QPointF to;
		const Object *enemy = nullptr;
		float dist = 10000;
		for (auto *obj: mind->getMapManager()->getVisibleObjects(unit)){
			if (mind->getFactionById(unit->getFactionId())->isFriendly(obj))
				continue;

			to = mind->physicsEngine()->getPosition(obj);
			if (Geometry::distance(to, from) < dist){
				enemy = obj;
				dist = Geometry::distance(to, from);
			}
		}
		unit->property(TempData::NearestDist) = dist;
		unit->setNearestEnemy(enemy);
	}
}



