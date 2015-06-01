/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
class MapManager;
class Unit;
class Object;
class QPointF;
class QPoint;


/**
 * @brief This class represents a map of accessible grid tiles (obtained by dicretizing the map).
 */
class AccessiblityMap {
public:
	AccessiblityMap(const MapManager *mapManager, const int gridSize);
	/**
	 * @brief True if the point is accessible.
	 *
	 * @param point ...
	 * @return bool
	 */
	virtual bool isAccessible(const Unit *unit, const QPoint &point) = 0;
	/**
	 * @brief Updates the accessibility map to take into account the new object.
	 */
	virtual void addObject(const Object *object, const QPointF &position) = 0;
	virtual void removeObject(const Object *object, const QPointF &position) = 0;

	/**
	 * @brief This method returns the discretized point. It chooses the closest point available out
	 */
	QPoint discretize(const QPointF &point) const;
	QPointF undiscretize(const QPoint &point) const;

protected:
	const int gridSize;
	const MapManager *mapManager;
};
