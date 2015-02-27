/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

class AnimatorHeal : public Animator {
public:
	AnimatorHeal(Mind *mind);

	void act();
private:
	const float epsilon = 1.5;
};

