/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once

class Object;
class QPointF;
class PhysicsEngine;
class Unit;
class VisibilityUpdate;


/**
 * @brief This class is a container for a visibility map.
 *
 * It can update and query the visibility of regions, points and objects.
 *
 */
class VisibilityMap {
public:
	/**
	 * @brief Updates the visibility map.
	 *
	 * Adds includeCircle from visibilityUpdate but ommits all ommitPolygons.
	 */
	virtual void update(const VisibilityUpdate &visibilityUpdate) = 0;
	/**
	 * @brief True if the point is visible in the map.
	 */
	virtual bool isVisible(const QPointF &point) const = 0;
	/**
	 * @brief True if any part of target is visible from from unit.
	 *
	 * @param physicsEngine Used for getting objects' positions. Might also be used for calculations.
	 * @return bool
	 */
	bool isVisible(const Unit *from, const Object *target, const PhysicsEngine *physicsEngine) const;
	/**
	 * @brief Clears the map.
	 *
	 * @return void
	 */
	virtual void clear() = 0;

protected:
	virtual bool isVisible(const Unit *from, const QPointF &target, const Object *owner,
			       const PhysicsEngine *physicsEngine) const = 0;
};
