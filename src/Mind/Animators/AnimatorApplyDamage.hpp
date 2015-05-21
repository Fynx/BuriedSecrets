/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorApplyDamage
 * Decreases health points of Units by damage value.
 */
class AnimatorApplyDamage : public Animator {
public:
	AnimatorApplyDamage(Mind *mind);

	void act();
};

