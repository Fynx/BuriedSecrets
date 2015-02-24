/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Graphics/AnimationSet.hpp"
#include <cassert>


AnimationSet::AnimationSet(const AnimationSet::SetType &animationSet)
	: animationSet{animationSet}
{}


AnimationSet::AnimationSet(AnimationSet::SetType && animationSet)
	: animationSet{std::move(animationSet)}
{}

const Animation *AnimationSet::getAnimationForState(const BS::State &state) const
{
 	auto it = animationSet.find(state);
	//FIXME TMP
	if (it == animationSet.end())
		it = animationSet.find(BS::State::Idle);

	assert(it != animationSet.end());
	return it.value();
}

