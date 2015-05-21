/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorEffects
 * Manages the Effects, restarts infinite ones after timeouts.
 */
class AnimatorEffects : public Animator {
public:
	AnimatorEffects(Mind *mind);

	void act();

private:
	QTime timer;
};


