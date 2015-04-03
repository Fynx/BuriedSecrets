/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

class AnimatorNearestEnemy : public Animator {
public:
	AnimatorNearestEnemy(Mind *mind);

	void act();
};


