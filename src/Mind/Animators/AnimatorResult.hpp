/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorResult
 * Modifies GameState. Deprecated.
 */
class AnimatorResult : public Animator {
public:
	AnimatorResult(Mind *mind);

	void act();
};


