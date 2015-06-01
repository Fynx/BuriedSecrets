/* YoLoDevelopment, 2014-2015
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

inline bool operator==(const VisibilityUpdate &a, const VisibilityUpdate &b) {
	return a.includeCircle == b.includeCircle && a.ommitPolygons == b.ommitPolygons;
}

typedef QList<VisibilityUpdate> VisibilityUpdateDiff;
