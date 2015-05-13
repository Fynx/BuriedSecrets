/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

class MapManager;
class Object;
class QPointF;

template<class T>
class QList;

class Unit;

/**
 * @brief This class represents an abstract pathfinder.
 */
class PathFinder {
public:
	PathFinder(const MapManager *mapManager);
	virtual ~PathFinder() = default;
	virtual QList<QPointF> getPath(const QPointF &source, const Unit *unit, const QPointF &target) = 0;
	virtual void addObject(const Object *object, const QPointF &position) = 0;
	virtual void removeObject(const Object *object, const QPointF &position) = 0;

protected:
	const MapManager *mapManager;
};
