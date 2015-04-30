/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Geometry.hpp"

#include <cmath>
#include <QDebug>


bool BS::Geometry::isZero(const float x)
{
	static const float eps = 0.001f;
	return fabs(x) <= eps;
}


bool operator==(const BS::Geometry::Circle& a, const BS::Geometry::Circle& b)
{
	return a.centre == b.centre && BS::Geometry::isZero(a.radius - b.radius);
}


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


/**
 * @brief A helper method able to tell if a point is on segment.
 */
bool onSegment(const float detVal, const QPointF &begin, const QPointF &end, const QPointF &point) {
	return BS::Geometry::isZero(detVal) && qMin(begin.x(), end.x()) <= point.x()  &&
			point.x() <= qMax(begin.x(), end.x()) && qMin(begin.y(), end.y()) <= point.y() &&
			point.y() <= qMax(begin.y(), end.y());
}


bool BS::Geometry::vectorsIntersect(const QPointF &aBegin, const QPointF &aEnd,
				    const QPointF &bBegin, const QPointF &bEnd)
{
	float d1 = det(aBegin, aEnd, bBegin);
	float d2 = det(aBegin, aEnd, bEnd);
	float d3 = det(bBegin, bEnd, aBegin);
	float d4 = det(bBegin, bEnd, aEnd);
	if (d1 * d2 < 0 && d3 * d4 < 0) {
		return true;
	}

	return onSegment(d1, aBegin, aEnd, bBegin) || onSegment(d2, aBegin, aEnd, bEnd) ||
			onSegment(d3, bBegin, bEnd, aBegin) || onSegment(d4, bBegin, bEnd, aEnd);
}


float BS::Geometry::det(const QPointF &a, const QPointF &b, const QPointF &c)
{
	return (a.x() * b.y() + a.y() * c.x() + b.x() * c.y()) - (c.x() * b.y() + c.y() * a.x() + b.x() * a.y());
}


int BS::Geometry::detSgn(const QPointF &a, const QPointF &b, const QPointF &c)
{
	const float detVal = det(a, b, c);
	return isZero(detVal) ? 0 : static_cast<int>(detVal / fabs(detVal));
}


bool BS::Geometry::toLeft(const QPointF &a, const QPointF &b, const QPointF &c)
{
	return det(a, b, c) < 0.0f;
}


bool BS::Geometry::inLine(const QPointF &a, const QPointF &b, const QPointF &c) {
	return detSgn(a, b, c) == 0;
}


QRectF BS::Geometry::scaleRect(const QRectF &rect, const float scale)
{
	QPointF centre = rect.center();
	QPointF newTopLeft = centre + (rect.topLeft() - centre) * scale;
	QPointF newBottomRight = centre + (rect.bottomRight() - centre) * scale;
	return QRectF{newTopLeft, newBottomRight};
}


bool BS::Geometry::pointInPolygon(const QPointF &point, const QList< QPointF > &polygon)
{
	qreal xMin, xMax, yMin, yMax;
	xMin = xMax = polygon.front().x();
	yMin = yMax = polygon.front().y();

	for (const auto &p : polygon) {
		xMin = qMin(xMin, p.x());
		xMax = qMax(xMax, p.x());
		yMin = qMin(yMin, p.y());
		yMax = qMax(yMax, p.y());
	}

	const float eps = (xMax - xMin) / 100.0f;
	QPointF rayBegin{xMin - eps, point.y()};
	QPointF rayEnd{point};
	int intersections = 0;

	QPointF prev = polygon.back();
	for (const QPointF &p : polygon) {
		if (vectorsIntersect(rayBegin, rayEnd, prev, p)) {
			++intersections;
		}
		prev = p;
	}

	return (intersections & 1) == 1;
}

