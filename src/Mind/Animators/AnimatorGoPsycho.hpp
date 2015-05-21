/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorGoPsycho
 * Checks Units' mental health and possibly removes them from Players' control.
 */
class AnimatorGoPsycho : public Animator {
public:
	AnimatorGoPsycho(Mind *mind);

	void act();
};


