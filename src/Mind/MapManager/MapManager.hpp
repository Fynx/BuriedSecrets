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
	 * @brief Registers the object on the map. From the time of invocation this object will be taken into account
	 * when calculating FOW, units visibility etc.
	 */
	void registerObject(const Object *object);
	/**
	 * @brief Updates FOW and visibility for units. Should be called after moving the units, before the AI needs
	 * the updated visibility.
	 */
	void updateFOW();

private:
	Map map;

	const PhysicsEngine *physicsEngine;
	const int playerFactionId;
};