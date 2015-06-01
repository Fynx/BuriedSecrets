/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Mind/MapManager/AccessibilityMap.hpp"


/**
 * @brief AccessibilityMap implementation which is just an interface for queries to MapManager.
 *
 * Nothing is cached, everything is computated on the fly.
 */
class DynamicAccessiblityMap : public AccessiblityMap {
public:
	DynamicAccessiblityMap(const MapManager *mapManager, const int gridSize);
	bool isAccessible(const Unit *unit, const QPoint &point) override;
	void addObject(const Object *object, const QPointF &position) override;
	void removeObject(const Object *object, const QPointF &position) override;
};
