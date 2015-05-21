/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class
 * Removes Units from Locations.
 */
class AnimatorLeaveBuilding : public Animator {
public:
	AnimatorLeaveBuilding(Mind *mind);

	void act();
};



