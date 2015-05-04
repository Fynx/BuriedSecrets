/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorTime.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Mind/Mind.hpp"

using namespace BS;

AnimatorTime::AnimatorTime(Mind *mind) : Animator(mind)
{
	info("Animator Time created.");
}

void AnimatorTime::act()
{
	mind->incSecsSinceBeginning();
}
