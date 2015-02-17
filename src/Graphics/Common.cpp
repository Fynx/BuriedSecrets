/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include <cmath>

#include "Graphics/Common.hpp"


float BS::Graphic::distance(const QPointF &a, const QPointF &b)
{
	return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}
