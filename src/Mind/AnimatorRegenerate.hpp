/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animator.hpp"

class AnimatorRegenerate : public Animator {
public:
	AnimatorRegenerate(Mind *mind);

	void act();
};

