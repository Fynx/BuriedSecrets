/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/SelectionEffectData.hpp"


SelectionEffectData::SelectionEffectData(const Object *object, const QColor color)
	: ObjectEffectData{object}, color{color}
{}


QColor SelectionEffectData::getColor() const
{
	return color;
}
