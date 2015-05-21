/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorTest.hpp"

#include "DebugManager/DebugManager.hpp"
#include "Mind/Mind.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"


AnimatorTest::AnimatorTest(Mind *mind) : Animator(mind)
{
	info("AnimatorTest created.");
}


void AnimatorTest::act()
{
	for (Object * obj : objects)
		mind->physicsEngine()->setVelocity(obj, QVector2D(4, 8));
}
