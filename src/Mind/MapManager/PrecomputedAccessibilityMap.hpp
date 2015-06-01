/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include "Mind/MapManager/AccessibilityMap.hpp"


/**
 * @brief This class represents a precomputed accessiblity map - a static capture of the accessibility.
 */
class PrecomputedAccessibilityMap : public AccessiblityMap {
public:
	PrecomputedAccessibilityMap(const MapManager *mapManager, const int gridSize, const Unit *unit);

	// There's no need for value semantics for this class.
	PrecomputedAccessibilityMap(const PrecomputedAccessibilityMap &other) = delete;
	PrecomputedAccessibilityMap(PrecomputedAccessibilityMap &&other) = delete;

	PrecomputedAccessibilityMap& operator=(const PrecomputedAccessibilityMap &other) = delete;
	PrecomputedAccessibilityMap& operator=(PrecomputedAccessibilityMap &&other) = delete;

	~PrecomputedAccessibilityMap();

	bool isAccessible(const Unit *unit, const QPoint &point) override;
	void addObject(const Object *object, const QPointF &position) override;
	void removeObject(const Object *object, const QPointF &position) override;

private:
	int width, height;
	bool **matrix;
	const Unit *unit;
};
