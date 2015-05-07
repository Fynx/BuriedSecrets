/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "Mind/Animators/Animator.hpp"

class AnimatorAnimate: public Animator {
public:
	AnimatorAnimate(Mind *mind);

	void act() override;
};
