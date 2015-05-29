/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorBAggresiveAtt
 * Sets targets for Units inside buildings and have aggressive attitude.
 */
class AnimatorBAggressiveAtt : public Animator {
public:
	AnimatorBAggressiveAtt(Mind *mind);

	void act() override;
};
