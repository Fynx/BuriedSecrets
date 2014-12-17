/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "Mind/Animator.hpp"

class AnimationAnimator: public Animator {
public:
	AnimationAnimator(Mind *mind);

	void act() override;

private:
	const int frameDuration = 700;	// in miliseconds
	int elapsedTime;
	QTime timer;
};