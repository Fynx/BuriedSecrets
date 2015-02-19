/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QtCore/QList>
#include <QtCore/QPointF>

#include "Common/Geometry.hpp"
#include "GameObjects/Object.hpp"
#include "Mind/MapManager/Map.hpp"
#include "Mind/MapManager/VisibilityUpdate.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"


/**
 * @brief This class manages the map representation and can answer questions about Field of View, Fog of War, points
 * visiblity and accessibility per faction.
 */
class MapManager {
public:
	typedef QList<VisibilityUpdate> VisibilityUpdateDiff;

	MapManager(const QJsonObject &json, const PhysicsEngine *physicsEngine, const int playerFactionId);

	const Map *getMap() const;
	/**
	 * @brief Returns a path from point from to point to.
	 */
	QList<QPointF> getPath(const QPointF &from, const QPointF &to) const;

	/**
	 * @brief True if a point can be walked onto.
	 */
	bool isAccessible(const QPointF &point) const;
	/**
	 * @brief True if the point has been seen by the faction.
	 */
	bool hasBeenSeen(const QPointF &point, const int factionId) const;

	/**
	 * @brief Returns the region currently visible to the units from the given faction.
	 */
	QList<BS::Geometry::Circle> getVisibleRegion(const int factionId) const;
	/**
	 * @brief Returns a list of all the objects visible to the units from faction factionId.
	 */
	QList<Object *> getVisibleObjects(const int factionId) const;

	/**
	 * @brief Clears the current Field of View of a faction. This should be called prior to updating FOV with a
	 * series of addVisibility calls.
	 * @param factionId The id of the faction for which the update should be performed.
	 */
	void clearFieldOfView(const int factionId);
	/**
	 * @brief Adds visibility to a faction. This method takes into account obstacles present.
	 *
	 * This updates FOV which automatically propagates to FOW.
	 *
	 * @param circle The circle potentially visible to the faction. We're assuming a unit in the centre of this
	 * circle.
	 * @param factionId The faction that should see the region.
	 */
	void addVisibility(const BS::Geometry::Circle circle, const int factionId);
	/**
	 * @brief Returns the diff of the visibility updates between the last call of this method and now.
	 *
	 * A call of this method discards the returned history. This call transfers the ownership of the returned
	 * pointer to the caller.
	 */
	VisibilityUpdateDiff *getVisibilityUpdatesDiff();

private:
	const int playerFactionId;
	Map map;
	QHash<int, VisibilityUpdateDiff> FOVs;	// Per-faction FOVs.

	const PhysicsEngine *physicsEngine;
	VisibilityUpdateDiff *visibilityUpdatesDiff;
};