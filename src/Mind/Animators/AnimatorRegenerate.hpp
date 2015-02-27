/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

class AnimatorRegenerate : public Animator {
public:
	AnimatorRegenerate(Mind *mind);

	void act();
};

