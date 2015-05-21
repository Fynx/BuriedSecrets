/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorMove
 * Executes Units' movement.
 */
class AnimatorMove : public Animator {
public:
	AnimatorMove(Mind *mind);

	void act();

private:
	const float epsilon = 0.5;
};

