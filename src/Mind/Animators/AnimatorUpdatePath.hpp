/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

class AnimatorUpdatePath : public Animator {
public:
	AnimatorUpdatePath(Mind *mind);

	void act();

private:
	const float epsilon = 0.5;
};

