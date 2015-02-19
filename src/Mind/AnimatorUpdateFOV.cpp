/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/AnimatorUpdateFOV.hpp"


AnimatorUpdateFOV::AnimatorUpdateFOV(Mind *mind): Animator{mind}
{}


void AnimatorUpdateFOV::act()
{
	factionPresent.clear();
	for (const Object *obj: objects) {
		BS::Geometry::Circle circle;
		circle.centre = mind->physicsEngine()->getPosition(obj);
		circle.radius = 5.0f;	// FIXME get this info from prototypes/properties

		int factionId = obj->getFactionId();
		if (factionPresent.count(factionId) == 0) {
			// This faction hasn't been updated yet, clear FOV.
			factionPresent.insert(factionId);
			mind->getMapManager()->clearFieldOfView(factionId);
		}

		mind->getMapManager()->addVisibility(circle, factionId);
	}
}

