/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/AnimatorTest.hpp"

//TODO use DebugManager instead
#include <QtCore>

#include "Mind/Mind.hpp"

AnimatorTest::AnimatorTest(Mind *mind) : Animator(mind)
{
	qDebug() << "AnimatorTest created.";
}

void AnimatorTest::act()
{
	for (Object * obj : objects){
		mind->physicsEngine()->setVelocity(obj, QVector2D(50, 45));
	}
}
