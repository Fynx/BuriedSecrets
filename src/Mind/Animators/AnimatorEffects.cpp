/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorEffects.hpp"

#include "Mind/Mind.hpp"
#include "DebugManager/DebugManager.hpp"


AnimatorEffects::AnimatorEffects(Mind *mind) : Animator(mind)
{
	info("AnimatorEffects created.");
}


void AnimatorEffects::act()
{
	auto effect = mind->getActiveEffects()->begin();
	while (effect != mind->getActiveEffects()->end()){
		if (effect->isInfinite()){
			effect++;
			continue;
		}
		effect->setTimeout(effect->getTimeout() - 1);

		if (effect->getTimeout() == 0)
			mind->deleteEffect(effect++);
		effect++;
	}
}

