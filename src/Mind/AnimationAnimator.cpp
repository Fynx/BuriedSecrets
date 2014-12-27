#include "Mind/AnimationAnimator.hpp"


AnimationAnimator::AnimationAnimator(Mind *mind)
	: Animator{mind}
{
}


void AnimationAnimator::act()
{
	for (auto &obj: objects) {
		int allFrames = obj->getPrototype()->getAnimationData(obj->getState())->getFramesNumber();
		int currentFrame = obj->getFrame();
		if (currentFrame + 1 >= allFrames) {
			obj->setState(BS::State::Idle);
		} else {
			obj->setFrame(currentFrame + 1);
		}
	}
}
