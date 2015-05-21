/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorNearCamp
 * Sets NearCamp flag depending on distance from given Unit to its Camp.
 */
class AnimatorNearCamp : public Animator {
public:
	AnimatorNearCamp(Mind *mind);

	void act();
};


