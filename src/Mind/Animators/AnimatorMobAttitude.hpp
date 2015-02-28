/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

class AnimatorMobAttitude : public Animator {
public:
	AnimatorMobAttitude(Mind *mind);

	void act();
};
