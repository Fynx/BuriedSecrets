/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Mind/MapManager/AccessibilityMap.hpp"


class DynamicAccessiblityMap : public AccessiblityMap {
public:
	DynamicAccessiblityMap(const MapManager *mapManager, const int gridSize);
	bool isAccessible(const Unit *unit, const QPoint &point) override;
};