#include "Mind/AnimationAnimator.hpp"


AnimationAnimator::AnimationAnimator(Mind *mind)
	: Animator{mind}, elapsedTime{0}
{
	timer.start();
}


void AnimationAnimator::act()
{
	auto deltaT = timer.elapsed();
	timer.restart();
	elapsedTime += deltaT;
	if (elapsedTime >= frameDuration) {
		elapsedTime -= frameDuration;

		for (auto &obj: objects) {
			// FIXME @Slagvi you will have to find a way to store the time for which the object has
			// already been animated. I don't know how you want to do it without storing those times *in*
			// the animator, but you wanted it that way (no additional per-object data in animators).
			int allFrames = obj->getPrototype()->getAnimationData(obj->getState())->getFramesNumber();
			int currentFrame = obj->getFrame();
			if (currentFrame + 1 >= allFrames) {
				obj->setState(BS::State::Idle);
				obj->setFrame(0);
			} else {
				obj->setFrame(currentFrame + 1);
			}
		}
	}
}
