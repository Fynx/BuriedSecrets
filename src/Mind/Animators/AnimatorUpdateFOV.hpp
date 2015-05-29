/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include <unordered_set>

#include "Mind/Animators/Animator.hpp"
#include "Mind/Mind.hpp"

/**
 * @class AnimatorUpdateFOV
 * Updates FOV depending on Units' depending on their sight range.
 */
class AnimatorUpdateFOV: public Animator {
public:
	AnimatorUpdateFOV(Mind *mind);
	void act() override;

private:
	std::unordered_set<int> factionPresent;
};
