/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

class AnimatorPhysicsUpdate : public Animator {
public:
	AnimatorPhysicsUpdate(Mind *mind);

	void act();
};

