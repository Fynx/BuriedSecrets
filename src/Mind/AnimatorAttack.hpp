/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animator.hpp"

class AnimatorAttack : public Animator {
public:
	AnimatorAttack(Mind *mind);

	void act();
};

