/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Mind/ObjectEffectData.hpp"


class ObjectRadiusEffectData : public ObjectEffectData {
public:
	ObjectRadiusEffectData(const Object *object, const float radius);

	float getRadius() const;

private:
	const float radius;
};