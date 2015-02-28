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
	for (auto effect = mind->getActiveEffects()->begin(); effect != mind->getActiveEffects()->end(); ++effect){
		if (effect->isInfinite())
			continue;
		effect->setTimeout(effect->getTimeout() - 1);

		if (effect->getTimeout() == 0)
			mind->deleteEffect(effect);
	}
}

