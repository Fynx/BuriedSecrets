#include "Mind/AnimatorTest.hpp"

//TODO use DebugManager instead
#include <QtCore>

AnimatorTest::AnimatorTest()
{
	qDebug() << "Animator created.";
}

void AnimatorTest::act()
{
	qDebug() << "TestAnimator to the rescue!";
}
