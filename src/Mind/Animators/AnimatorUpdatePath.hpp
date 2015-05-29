/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

class Unit;

/**
 * @class AnimatorUpdatePath
 * Calculates and modifies Units' paths.
 */
class AnimatorUpdatePath : public Animator {
public:
	AnimatorUpdatePath(Mind *mind);

	void act() override;

private:
	bool isStuck(Unit *unit, const QPoint &position);

	const float epsilon = 0.5;
	const int burnout = 1500;
	QTime timer;
};

