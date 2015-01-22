/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animator.hpp"

class AnimatorConstruct : public Animator {
public:
	AnimatorConstruct(Mind *mind);

	void act();
private:
	const float epsilon = 3.5;
};

