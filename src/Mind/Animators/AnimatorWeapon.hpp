/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorWeapon
 * Modifies Weapons' states.
 */
class AnimatorWeapon : public Animator {
public:
	AnimatorWeapon(Mind *mind);

	void act() override;
};

