/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animator.hpp"


// Works on faction, consumes food supplies
class AnimatorConsume : public Animator {
public:
	AnimatorConsume(Mind *mind);

	void act();
};
