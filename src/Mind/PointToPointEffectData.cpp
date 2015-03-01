/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/PointToPointEffectData.hpp"


PointToPointEffectData::PointToPointEffectData(const QPointF &source, const QPointF &destination)
	: EffectData{}, source{source}, destination{destination}
{}


QPointF PointToPointEffectData::getSource() const
{
	return source;
}


QPointF PointToPointEffectData::getDestination() const
{
	return destination;
}

