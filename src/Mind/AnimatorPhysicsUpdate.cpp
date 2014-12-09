/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/AnimatorPhysicsUpdate.hpp"

#include <QtCore>

#include "Mind/Mind.hpp"

AnimatorPhysicsUpdate::AnimatorPhysicsUpdate(Mind *mind) : Animator(mind)
{
	qDebug() << "AnimatorPhysicsUpdate created.";
}


void AnimatorPhysicsUpdate::act()
{
	mind->physicsEngine()->updatePhysics(40);
}
