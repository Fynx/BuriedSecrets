/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/ObjectRadiusEffectData.hpp"


ObjectRadiusEffectData::ObjectRadiusEffectData(const Object *object, const float radius)
	: ObjectEffectData{object}, radius{radius}
{}


float ObjectRadiusEffectData::getRadius() const
{
	return radius;
}
