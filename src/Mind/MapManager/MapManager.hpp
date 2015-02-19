/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QtCore/QList>
#include <QtCore/QPointF>

#include "Common/Geometry.hpp"
#include "GameObjects/Object.hpp"
#include "Mind/MapManager/Map.hpp"
#include "PhysicsEngine/PhysicsEngine.hpp"


/**
 * @brief This class manages the map representation and can answer questions about Field of View, Fog of War, points
 * visiblity and accessibility per faction.
 */
class MapManager {
public:
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

private:
	Map map;

	const PhysicsEngine *physicsEngine;
	const int playerFactionId;
};