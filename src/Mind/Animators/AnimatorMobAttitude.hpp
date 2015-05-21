/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorMobAttitude
 * Simple AI Animator.
 * Sets Units' Commands depending on hostile Units in the vicinity.
 */
class AnimatorMobAttitude : public Animator {
public:
	AnimatorMobAttitude(Mind *mind);

	void act();
};
