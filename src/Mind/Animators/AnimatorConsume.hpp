/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorConsume
 * Works on faction, consumes food supplies.
 */
class AnimatorConsume : public Animator {
public:
	AnimatorConsume(Mind *mind);

	void act();
};
