/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

class AnimatorMove : public Animator {
public:
	AnimatorMove(Mind *mind);

	void act();

private:
	const float epsilon = 1.5;
};
