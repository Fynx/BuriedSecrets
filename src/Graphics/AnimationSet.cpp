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
	assert(it != animationSet.end());
	return it.value();
}

