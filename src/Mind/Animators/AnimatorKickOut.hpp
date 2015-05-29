/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorKickOut
 * Kicks Units out of Locations in which they are not supposed to be.
 */
class AnimatorKickOut : public Animator {
public:
	AnimatorKickOut(Mind *mind);

	void act() override;
};
