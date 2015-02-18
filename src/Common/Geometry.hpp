/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <QPointF>


namespace BS {
	namespace Geometry {
		struct Circle {
			QPointF centre;
			float radius;
		};

		float distance(const QPointF &a, const QPointF &b);
	}
}