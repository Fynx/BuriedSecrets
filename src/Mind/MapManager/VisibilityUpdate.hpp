/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include "Common/Geometry.hpp"


/**
 * @brief This is a small helper struct to be used to store data about FOV updates.
 */
struct VisibilityUpdate {
	BS::Geometry::Circle includeCircle;
	QList<BS::Geometry::Polygon> ommitPolygons;
};