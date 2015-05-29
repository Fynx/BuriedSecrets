/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorTime
 * Updates global time.
 */
class AnimatorTime : public Animator {
public:
	AnimatorTime(Mind *mind);

	void act() override;
};
