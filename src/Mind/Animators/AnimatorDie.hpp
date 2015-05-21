/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorDie
 * Kills Units when their HP level reach 0.
 */
class AnimatorDie : public Animator {
public:
	AnimatorDie(Mind *mind);

	void act();
};

