/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/MapManager/DynamicAccessibilityMap.hpp"

#include "Mind/MapManager/MapManager.hpp"


DynamicAccessiblityMap::DynamicAccessiblityMap(const MapManager *mapManager, const int gridSize)
		: AccessiblityMap{mapManager, gridSize}
{}


bool DynamicAccessiblityMap::isAccessible(const Unit *unit, const QPoint &point)
{
	return mapManager->canStandOn(unit, undiscretize(point));
}
