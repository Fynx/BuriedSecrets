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


QVector2D BS::Geometry::angleToVec(float a)
{
	a = a*M_PI / 180;
	return QVector2D(cos(a), sin(a));
}


bool BS::Geometry::inCircle(const QPointF &p, const BS::Geometry::Circle &circle)
{
	return distance(p, circle.centre) <= circle.radius;
}


bool BS::Geometry::circlesIntersect(const BS::Geometry::Circle &a, const BS::Geometry::Circle &b)
{
	return distance(a.centre, b.centre) < (a.radius + b.radius);
}


float BS::Geometry::det(const QPointF &a, const QPointF &b, const QPointF &c)
{
	return (a.x() * b.y() + a.y() * c.x() + b.x() * c.y()) - (c.x() * b.y() + c.y() * a.x() + b.x() * a.y());
}


bool BS::Geometry::toLeft(const QPointF &a, const QPointF &b, const QPointF &c)
{
	return det(a, b, c) < 0.0f;
}
