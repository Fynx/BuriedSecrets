/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QtCore/QHash>

#include "Common/Enums.hpp"
#include "Graphics/Animation.hpp"

/**
 * @brief This class represents a complete set of animations for a GraphicalEntity.
 *
 * FIXME Memory footprint of this could be reduced if it was stored in the GraphicalDataManager uniquely, but it's just
 *  RAM so might not be worth the fuss.
 */
class AnimationSet {
public:
	typedef QHash<BS::State, const Animation *> SetType;
	AnimationSet(const SetType &animationSet);
	AnimationSet(SetType && animationSet);

	const Animation *getAnimationForState(const BS::State &state) const;

private:
	SetType animationSet;
};