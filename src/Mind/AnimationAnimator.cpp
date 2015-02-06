#include "Mind/AnimationAnimator.hpp"
#include "DebugManager/DebugManager.hpp"


AnimationAnimator::AnimationAnimator(Mind *mind)
	: Animator{mind}
{
	info("AnimationAnimator created.");
}


void AnimationAnimator::act()
{
	for (auto &obj: objects) {
		if (obj->getState() == BS::State::Inside)
			continue;
		int allFrames = obj->getPrototype()->getAnimationData(obj->getState())->getFramesNumber();
		int currentFrame = obj->getFrame();
		if (currentFrame + 1 >= allFrames) {
			obj->setState(BS::State::Idle);
		} else {
			obj->setFrame(currentFrame + 1);
		}
	}
}
