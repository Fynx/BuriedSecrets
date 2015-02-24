/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animator.hpp"

class AnimatorWatchTarget : public Animator {
public:
	AnimatorWatchTarget(Mind *mind);

	void act();
};


