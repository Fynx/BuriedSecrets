/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "Mind/Animators/Animator.hpp"

class AnimationAnimator: public Animator {
public:
	AnimationAnimator(Mind *mind);

	void act() override;
};
