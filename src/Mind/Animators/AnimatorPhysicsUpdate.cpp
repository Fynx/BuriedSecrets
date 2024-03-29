/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorPhysicsUpdate.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Mind/Mind.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"


AnimatorPhysicsUpdate::AnimatorPhysicsUpdate(Mind *mind) : Animator(mind)
{
	info("AnimatorPhysicsUpdate created.");
}


void AnimatorPhysicsUpdate::act()
{
	mind->physicsEngine()->updatePhysics(40);
}
