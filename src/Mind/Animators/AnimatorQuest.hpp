/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

#include "Mind/Animators/Animator.hpp"

/**
 * @class AnimatorQuest
 * Checks start, failure and success conditions for Quests and changes Quests' states.
 */
class AnimatorQuest : public Animator {
public:
	AnimatorQuest(Mind *mind);

	void act() override;
};
