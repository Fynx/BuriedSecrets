/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/MapManager/PrecomputedAccessibilityMap.hpp"

#include <QImage>

#include "GameObjects/Unit.hpp"
#include "Mind/MapManager/MapManager.hpp"


PrecomputedAccessibilityMap::PrecomputedAccessibilityMap(const MapManager *mapManager, const int gridSize,
							 const Unit *unit)
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
	
        // Debug
// 	QSizeF mapSize = mapManager->getMap()->getSize();
// 	QImage image{mapSize.toSize(), QImage::Format_ARGB32};
// 	image.fill(Qt::transparent);
// 	QPainter painter{&image};
// 	painter.setBrush(QBrush(Qt::black));
// 
// 	for (int x = 0; x < width; ++x) {
// 		for (int y = 0; y < height; ++y) {
// 			if (!matrix[x][y]) {
// 				painter.drawRect(x * gridSize, y * gridSize, gridSize, gridSize);
// 			}
// 		}
// 	}
// 
// 	qDebug() << unit->getName();
// 	image.save("/tmp/" + unit->getName() + ".png");
	// End of Debug
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

