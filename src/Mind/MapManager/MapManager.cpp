/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/MapManager/MapManager.hpp"


MapManager::MapManager(const QJsonObject &json, const PhysicsEngine *physicsEngine, const int playerFactionId)
	: playerFactionId{playerFactionId}, map{json}, physicsEngine{physicsEngine},
	visibilityUpdatesDiff{new VisibilityUpdateDiff{}}
{}


const Map *MapManager::getMap() const
{
	return &map;
}


QList<QPointF> MapManager::getPath(const QPointF &from, const QPointF &to) const
{
	QList<QPointF> result{to};

	// TODO

	return result;
}


void MapManager::clearFieldOfView(const int factionId)
{
	FOVs[factionId].clear();
}


void MapManager::addVisibility(const BS::Geometry::Circle circle, const int factionId)
{
	// FOV
	VisibilityUpdate update;
	update.includeCircle = circle;
	// TODO actual visibility (exclude area behind buildings etc).
	FOVs[factionId].append(update);
	if (factionId == playerFactionId) {
		visibilityUpdatesDiff->append(update);
	}
	// TODO FOW
}


MapManager::VisibilityUpdateDiff * MapManager::getVisibilityUpdatesDiff()
{
	auto *ptr = visibilityUpdatesDiff;
	visibilityUpdatesDiff = new VisibilityUpdateDiff{};
	return ptr;
}


