/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Mind/MapManager/AccessibilityMap.hpp"


/**
 * @brief This class represents a precomputed accessiblity map - a static capture of the accessibility.
 *
 */
class PrecomputedAccessibilityMap : public AccessiblityMap {
public:
	PrecomputedAccessibilityMap(const MapManager *mapManager, const int gridSize, const Unit *unit);

	// No time to write those, and having them wouldn't give us anything anyway.
	PrecomputedAccessibilityMap(const PrecomputedAccessibilityMap &other) = delete;
	PrecomputedAccessibilityMap(PrecomputedAccessibilityMap &&other) = delete;

	PrecomputedAccessibilityMap& operator=(const PrecomputedAccessibilityMap &other) = delete;
	PrecomputedAccessibilityMap& operator=(PrecomputedAccessibilityMap &&other) = delete;

	~PrecomputedAccessibilityMap();

	bool isAccessible(const Unit *unit, const QPoint &point) override;

private:
	int width, height;
	bool **matrix;
};