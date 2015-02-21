/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QList>
#include <QPointF>
#include <QVector2D>


namespace BS {
	namespace Geometry {
		struct Circle {
			QPointF centre;
			float radius;
		};

		typedef QList<QPointF> Polygon;

		float distance(const QPointF &a, const QPointF &b);
		float vecToAngle(const QVector2D &v);
		QVector2D angleToVec(float a);
	}
}
