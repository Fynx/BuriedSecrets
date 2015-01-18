/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/AnimatorPhysicsUpdate.hpp"

#include "Mind/Mind.hpp"
#include "DebugManager/DebugManager.hpp"


AnimatorPhysicsUpdate::AnimatorPhysicsUpdate(Mind *mind) : Animator(mind)
{
	info("AnimatorPhysicsUpdate created.");
}


void AnimatorPhysicsUpdate::act()
{
	mind->physicsEngine()->updatePhysics(40);
}
