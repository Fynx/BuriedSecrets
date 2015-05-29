/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorAggressiveAtt
 * Finds the nearest enemy and sets it as target.
 */
class AnimatorAggressiveAtt : public Animator {
public:
	AnimatorAggressiveAtt(Mind *mind);

	void act() override;
};
