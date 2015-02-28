/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/ShotEffectData.hpp"


ShotEffectData::ShotEffectData(const Object *object, QPointF destination)
	: ObjectEffectData{object}, dest{destination}
{}


ShotEffectData::~ShotEffectData()
{}


QPointF ShotEffectData::getDestination() const
{
	return dest;
}
