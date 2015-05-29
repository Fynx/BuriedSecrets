/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorDie
 * Kills Units when their HP level reaches 0.
 */
class AnimatorDie : public Animator {
public:
	AnimatorDie(Mind *mind);

	void act() override;
};
