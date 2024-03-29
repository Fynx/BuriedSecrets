/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorAsseble
 * In case of Assemble command, puts a visible Object on the map.
 */
class AnimatorAssemble : public Animator {
public:
	AnimatorAssemble(Mind *mind);

	void act() override;

private:
	const float epsilon = 5;
};

