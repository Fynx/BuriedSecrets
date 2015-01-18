/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animator.hpp"

class AnimatorUpdatePath : public Animator {
public:
	AnimatorUpdatePath(Mind *mind);

	void act();
};

