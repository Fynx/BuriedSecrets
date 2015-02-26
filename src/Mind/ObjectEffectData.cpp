/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/ObjectEffectData.hpp"


ObjectEffectData::ObjectEffectData(const Object *object)
	: EffectData{}, object{object}
{}


ObjectEffectData::~ObjectEffectData()
{}


const Object *ObjectEffectData::getObject() const
{
	return object;
}
