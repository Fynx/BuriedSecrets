/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorAttack
 * Reacts to Attack command given to a Unit.
 */
class AnimatorAttack : public Animator {
public:
	AnimatorAttack(Mind *mind);

	void act() override;
};

