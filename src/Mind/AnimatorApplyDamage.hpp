/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animator.hpp"

class AnimatorApplyDamage : public Animator {
public:
	AnimatorApplyDamage(Mind *mind);

	void act();
};

