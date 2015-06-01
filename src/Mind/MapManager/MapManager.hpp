/* YoLoDevelopment, 2014-2015
 * All rights reserved.
 */
#pragma once
#include <cassert>

#include <QtCore/QList>
#include <QtCore/QPointF>

#include "Common/Geometry.hpp"
#include "DebugManager/DebugManager.hpp"
#include "Mind/MapManager/Map.hpp"
#include "Mind/MapManager/DiffVisibilityMap.hpp"
#include "Mind/MapManager/ImageVisibilityMap.hpp"
#include "Mind/MapManager/VisibilityMap.hpp"
#include "Mind/MapManager/VisibilityUpdate.hpp"

class Mind;
class Object;
class PathFinder;
class PhysicsEngine;
class Unit;


/**
 * @brief This class manages the map representation and can answer questions about Field of View, Fog of War, points'
 * visiblity and accessibility per faction. It needs to be updated about the creation and deletion of every object after
 * it is instantiated, since it manages its internal view of the map.
 */
class MapManager {
public:
	MapManager(const QJsonObject &json, const Mind *mind, const PhysicsEngine *physicsEngine,
			const int playerFactionId);
	~MapManager();

	const Map *getMap() const;
	/**
	 * @brief Returns a path from point from to point to.
	 */
	QList<QPointF> getPath(const Unit *unit, const QPointF &to);

	/**
	 * @brief Adds the object to the internal reprsentation of the map.
	 */
	void addObject(const Object *object);
	/**
	 * @brief Removes the object from the internal representation of the map.
	 */
	void removeObject(const Object *object, const QPointF &position);

	/**
	 * @brief True if a point can be walked onto.
	 */
	bool isAccessible(const QPointF &point) const;
	/**
	 * @brief True if the object created from the given prototype can stand on the point.
	 */
	bool canStandOn(const Unit *unit, const QPointF &point) const;
	/**
	 * @brief True if the object can be seen by the faction.
	 *
	 * NOT IMPLEMENTED.
	 */
	bool canBeSeen(const Object *object, const int factionId) const;
	/**
	 * @brief True if the object can be seen by the player's faction.
	 */
	bool canBeSeen(const Object *object) const;
	/**
	 * @brief True if the point has been seen by the faction.
	 */
	bool hasBeenSeen(const QPointF &point, const int factionId) const;
	bool hasBeenSeen(const Object *object, const int factionId) const;
	/**
	 * @brief True if the object has been seen by the player's faction.
	 */
	bool hasBeenSeen(const Object *object) const;

	bool pointInObject(const QPointF &point, const Object *object, const float inflate = 0.0f) const;
	/**
	 * @brief This method returns an Object containing the point or nullptr if no such object exists.
	 *
	 * WARNING: This method ignores units! It can return any Object except a unit. If you need the unit for some
	 * reason, please rename this method and create another one for units.
	 */
	const Object *getObjectContaining(const QPointF &point, const float inflate = 0.0f) const;

	/**
	 * @brief Returns the region currently visible to the units from the given faction.
	 *
	 * NOT IMPLEMENTED.
	 */
	VisibilityUpdateDiff getVisibleRegion(const int factionId) const;
	/**
	 * @brief Returns the region currently visible to the player's faction.
	 */
	VisibilityUpdateDiff getVisibleRegion() const;
	/**
	 * @brief Returns a list of all the objects visible to the units from faction factionId.
	 *
	 * This is an approximation.
	 */
	QList<const Object *> getVisibleObjects(const int factionId) const;
	/**
	 * @brief Returns a list of all the objects visible to the unit.
	 *
	 * This is an approximation.
	 */
	QList<const Object *> getVisibleObjects(const Unit *unit) const;

	/**
	 * @brief Clears the current Field of View of a faction. This should be called prior to updating FOV with a
	 * series of addVisibility calls.
	 * @param factionId The id of the faction for which the update should be performed.
	 */
	void clearFieldOfView(const int factionId);
	/**
	 * @brief Adds visibility of a unit to a faction. This method takes into account obstacles present.
	 *
	 * This updates FOV which automatically propagates to FOW.
	 *
	 * @param unit The unit which FOV should be added.
	 * @param factionId The faction that should see the region.
	 */
	void addVisibility(const Unit *unit, const BS::Geometry::Circle &circle, const int factionId);
	/**
	 * @brief Adds arbitrary visibility to the faction's FOV.
	 *
	 * This updates FOV which automatically propagates to FOW.
	 *
	 * @param factionId The faction that should see the region.
	 */
	void addVisibility(const BS::Geometry::Circle &circle, const int factionId);
	/**
	 * @brief Returns the diff of the visibility updates between the last call of this method and now.
	 *
	 * A call of this method discards the returned history. This call transfers the ownership of the returned
	 * pointer to the caller.
	 */
	VisibilityUpdateDiff *getVisibilityUpdatesDiff();

private:
	/**
	 * @brief Returns a point slightly out of circle which lies on the line which contains the centre and point p.
	 * Of the 2 possible points, the one closer to p is chosen.
	 */
	QPointF getPointOnCircleInline(const BS::Geometry::Circle &circle, const QPointF &p);

	const int playerFactionId;
	Map map;
	QHash<int, DiffVisibilityMap> FOVs;	// Per-faction FOVs.
	QHash<int, ImageVisibilityMap> FOWs;
	QHash<const Unit *, BS::Geometry::Circle> lastCircle;

	const PhysicsEngine *physicsEngine;
	PathFinder *pathFinder;
	VisibilityUpdateDiff *visibilityUpdatesDiff;
	ImageVisibilityMap playerFOV;
};


