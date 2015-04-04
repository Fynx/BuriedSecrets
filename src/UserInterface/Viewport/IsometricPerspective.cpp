/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "UserInterface/Viewport/IsometricPerspective.hpp"
#include <qabstractitemmodel.h>


IsometricPerspective::IsometricPerspective(const float scale)
	: Perspective{scale}
{}


QPointF IsometricPerspective::fromPixelsToBase(const QPointF &transformedPoint) const
{
	return QPointF{transformedPoint.x(), transformedPoint.y() * isometricYScale};
}


QPointF IsometricPerspective::fromBaseToPixels(const QPointF &scaledPoint) const
{
	return QPointF{scaledPoint.x(), scaledPoint.y() / isometricYScale};
}
