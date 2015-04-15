/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/MapManager/PrecomputedAccessibilityMap.hpp"

#include "Mind/MapManager/MapManager.hpp"


PrecomputedAccessibilityMap::PrecomputedAccessibilityMap(const MapManager *mapManager, const int gridSize,
							 const Unit* unit)
	: AccessiblityMap{mapManager, gridSize}
{
	QSizeF size = mapManager->getMap()->getSize();
	QPoint sizeP = discretize(QPointF{size.width(), size.height()});
	width = sizeP.x() + 1;
	height = sizeP.y() + 1;

	matrix = new bool*[width];
	for (int i = 0; i < width; ++i) {
		matrix[i] = new bool[height];
		for (int j = 0; j < height; ++j) {
			matrix[i][j] = mapManager->canStandOn(unit, undiscretize(QPoint{i, j}));
		}
	}
}


PrecomputedAccessibilityMap::~PrecomputedAccessibilityMap()
{
	for (int i = 0; i < width; ++i) {
		delete[] matrix[i];
	}

	delete[] matrix;
}


bool PrecomputedAccessibilityMap::isAccessible(const Unit *unit, const QPoint &point)
{
	assert(point.x() >= 0 && point.x() < width && point.y() >= 0 && point.y() < height);
	return matrix[point.x()][point.y()];
}

