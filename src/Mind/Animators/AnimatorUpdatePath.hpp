/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

class Unit;


class AnimatorUpdatePath : public Animator {
public:
	AnimatorUpdatePath(Mind *mind);

	void act();

private:
	bool isStuck(Unit *unit, const QPoint &position);

	const float epsilon = 0.5;
};

