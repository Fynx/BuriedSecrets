/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorEffects.hpp"

#include "Mind/Mind.hpp"
#include "DebugManager/DebugManager.hpp"


AnimatorEffects::AnimatorEffects(Mind *mind) : Animator(mind)
{
	info("AnimatorEffects created.");
	timer.start();
}


void AnimatorEffects::act()
{
	const int timeDelta = timer.elapsed();
	timer.restart();
	auto effect = mind->getActiveEffects()->begin();
	while (effect != mind->getActiveEffects()->end()) {
		auto nextEffect = effect;
		nextEffect++;

		if (!effect->isInfinite()) {
			if (effect->getTimeout() - timeDelta <= 0)
				mind->deleteEffect(effect);
			else
				effect->setTimeout(effect->getTimeout() - timeDelta);
		}

		effect = nextEffect;
	}
}

