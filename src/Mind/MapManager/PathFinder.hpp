/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <QList>

class MapManager;
class Object;
class QPointF;

/**
 * @brief This class represents an abstract pathfinder.
 */
class PathFinder {
public:
	PathFinder(const MapManager *mapManager);
	virtual QList<QPointF> getPath(const Object *object, const QPointF &target) = 0;

protected:
	const MapManager *mapManager;
};