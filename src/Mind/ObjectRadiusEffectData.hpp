/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Mind/ObjectEffectData.hpp"


/**
 * @brief EffectData for effects that need an object and a radius as input.
 */
class ObjectRadiusEffectData : public ObjectEffectData {
public:
	ObjectRadiusEffectData(const Object *object, const float radius);

	float getRadius() const;

private:
	const float radius;
};
