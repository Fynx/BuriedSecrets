/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#include "Mind/MapManager/AccessibilityMap.hpp"

#include <QtCore/QPointF>
#include <QtCore/QPoint>


AccessiblityMap::AccessiblityMap(const MapManager *mapManager, const int gridSize)
		: gridSize{gridSize}, mapManager{mapManager}
{}


QPoint AccessiblityMap::discretize(const QPointF &point) const
{
	return (point / gridSize).toPoint();
}


QPointF AccessiblityMap::undiscretize(const QPoint &point) const
{
	QPointF p{point};
	return p * gridSize + QPointF{gridSize / 2.0f, gridSize / 2.0f};
}

