/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

class AnimatorDisassemble : public Animator {
public:
	AnimatorDisassemble(Mind *mind);

	void act();
private:
	const float epsilon = 3.5;
};


