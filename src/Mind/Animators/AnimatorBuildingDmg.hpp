/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorBuildingDmg
 * Distributes damage among Units in buildings.
 */
class AnimatorBuildingDmg : public Animator {
public:
	AnimatorBuildingDmg(Mind *mind);

	void act() override;
};
