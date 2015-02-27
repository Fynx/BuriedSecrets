/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/Animators/AnimatorTest.hpp"

#include "Mind/Mind.hpp"
#include "DebugManager/DebugManager.hpp"


AnimatorTest::AnimatorTest(Mind *mind) : Animator(mind)
{
	info("AnimatorTest created.");
}


void AnimatorTest::act()
{
	for (Object * obj : objects){
		mind->physicsEngine()->setVelocity(obj, QVector2D(4, 8));
	}
}
