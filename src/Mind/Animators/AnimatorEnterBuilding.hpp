/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorEnterBuilding
 * Reacts to Units entering Locations.
 */
class AnimatorEnterBuilding : public Animator {
public:
	AnimatorEnterBuilding(Mind *mind);

	void act();
private:
	const float epsilon = 1;
};


