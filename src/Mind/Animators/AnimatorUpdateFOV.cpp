/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Common/Geometry.hpp"
#include "GameObjects/Unit.hpp"
#include "Mind/Animators/AnimatorUpdateFOV.hpp"
#include "Mind/MapManager/MapManager.hpp"


AnimatorUpdateFOV::AnimatorUpdateFOV(Mind *mind): Animator{mind}
{}


void AnimatorUpdateFOV::act()
{
	factionPresent.clear();
	for (const Object *obj: objects) {
		const Unit *unit = static_cast<const Unit *>(obj);
		if (unit != nullptr) {
			BS::Geometry::Circle circle;
			if (unit->getState() != BS::State::Inside)
				circle.centre = mind->physicsEngine()->getPosition(obj);
			else
				circle.centre = mind->physicsEngine()->getPosition(unit->getLocation());
			circle.radius = unit->getSightRange();

			int factionId = obj->getFactionId();
			if (factionPresent.count(factionId) == 0) {
				// This faction hasn't been updated yet, clear FOV.
				factionPresent.insert(factionId);
				mind->getMapManager()->clearFieldOfView(factionId);
			}

			mind->getMapManager()->addVisibility(unit, circle, factionId);
		}
	}
}

