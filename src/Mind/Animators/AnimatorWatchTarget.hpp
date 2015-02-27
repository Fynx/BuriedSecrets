/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

class AnimatorWatchTarget : public Animator {
public:
	AnimatorWatchTarget(Mind *mind);

	void act();
};


