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
	/**
	 * @brief Returns a path from source to target for the given unit.
	 *
	 * The path should possibly be short and computed as fast as possible, but there really are no enforced
	 * constraints on the implementation of this method.
	 */
	virtual QList<QPointF> getPath(const QPointF &source, const Unit *unit, const QPointF &target) = 0;
	/**
	 * @brief A hook called whenever a new object appears on map.
	 *
	 * Reimplement this to notify the internal data of the path finder implementation of the changes in the world.
	 *
	 * @param object The object to be added.
	 * @param position The position at which the object shall appear.
	 */
	virtual void addObject(const Object *object, const QPointF &position) = 0;
	/**
	 * @brief A hook called whenever a new object is deleted from the map.
	 *
	 * Reimplement this to notify the internal data of the path finder implementation of the changes in the world.
	 *
	 * @param object The object to be deleted.
	 * @param position The position at which the object was just before the deletion.
	 */
	virtual void removeObject(const Object *object, const QPointF &position) = 0;

protected:
	const MapManager *mapManager;
};
