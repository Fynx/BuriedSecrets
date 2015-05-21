/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorTest
 * Test Animator.
 */
class AnimatorTest : public Animator {
public:
	AnimatorTest(Mind *mind);

	void act();
};
