/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Geometry.hpp"

#include <cmath>


float BS::Geometry::distance(const QPointF &a, const QPointF &b)
{
	return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}