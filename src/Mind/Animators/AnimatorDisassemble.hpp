/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorDisasseble
 * Disassebles given visible Object into components and puts them in Equipment.
 */
class AnimatorDisassemble : public Animator {
public:
	AnimatorDisassemble(Mind *mind);

	void act();
private:
	const float epsilon = 5.5;
};


