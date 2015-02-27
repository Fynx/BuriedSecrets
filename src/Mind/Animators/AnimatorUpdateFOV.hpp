/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <unordered_set>

#include "Mind/Animators/Animator.hpp"
#include "Mind/Mind.hpp"


class AnimatorUpdateFOV: public Animator {
public:
	AnimatorUpdateFOV(Mind *mind);
	void act() override;

private:
	std::unordered_set<int> factionPresent;
};
