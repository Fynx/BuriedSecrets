/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/PointEffectData.hpp"


PointEffectData::PointEffectData(const QPointF &point)
	: EffectData{}, point{point}
{}


QPointF PointEffectData::getPoint() const
{
	return point;
}

