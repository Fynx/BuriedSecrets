/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorNearestEnemy
 * Sets nearest enemy for given Unit.
 */
class AnimatorNearestEnemy : public Animator {
public:
	AnimatorNearestEnemy(Mind *mind);

	void act() override;
};
