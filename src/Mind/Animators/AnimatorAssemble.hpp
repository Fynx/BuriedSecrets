/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

class AnimatorAssemble : public Animator {
public:
	AnimatorAssemble(Mind *mind);

	void act();
private:
	const float epsilon = 5;
};

