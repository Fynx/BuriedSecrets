/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorGuardAtt
 * Reacts to Units' set attitude depending on vicinity.
 */
class AnimatorGuardAtt : public Animator {
public:
	AnimatorGuardAtt(Mind *mind);

	void act() override;
};
