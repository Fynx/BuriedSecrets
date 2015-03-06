/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <cmath>

#include <QList>
#include <QPointF>
#include <QRectF>
#include <QVector2D>


namespace BS {
	namespace Geometry {
		const float PI = 3.1415926535f;
		typedef QList<QPointF> Polygon;

		struct Circle {
			Circle() {
				radius = 0.0f;
			};

			Circle(const QPointF &centre, const float radius) : centre{centre}, radius{radius}
			{}

			float getLength() const {
				return 2.0f * PI * radius;
			}
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
		QRectF scaleRect(const QRectF &rect, const float scale);
	}
}
