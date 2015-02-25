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

		struct Line {
			Line() {
				A = B = C = 0.0f;
			}

			Line(const QPointF &a, const QPointF &b) {
				QPointF delta = b - a;
				A = -delta.y();
				B = delta.x();
				C = a.x() * delta.y() - a.y() * delta.x();
			}

			float getY(const float x) const {
				return (-C - A * x) / B;
			}

			float A, B, C;
		};

		typedef QList<QPointF> Polygon;

		float distance(const QPointF &a, const QPointF &b);
		float vecToAngle(const QVector2D &v);
		QVector2D angleToVec(float a);
		bool inCircle(const QPointF &p, const Circle &circle);
		bool circlesIntersect(const Circle &a, const Circle &b);
		float det(const QPointF &a, const QPointF &b, const QPointF &c);
		/**
		 * @brief True if c is to the left of the vector from a to b. False otherwise.
		 */
		bool toLeft(const QPointF &a, const QPointF &b, const QPointF &c);
	}
}
