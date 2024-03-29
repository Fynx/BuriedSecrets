/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorWatchTarget
 * Updates orientation of Units'.
 */
class AnimatorWatchTarget : public Animator {
public:
	AnimatorWatchTarget(Mind *mind);

	void act() override;
};


