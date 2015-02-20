/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Geometry.hpp"

#include <cmath>


float BS::Geometry::distance(const QPointF &a, const QPointF &b)
{
	return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}


float BS::Geometry::vecToAngle(const QVector2D &v)
{
	return std::atan2(v.y(), v.x()) / M_PI * 180.0;
}


QVector2D BS::Geometry::angleToVec(const int a)
{
	return QVector2D(sin(a), cos(a));
}
