/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Mind/MapManager/MapManager.hpp"

MapManager::MapManager(const QJsonObject &json)
	: map(json)
{}

const Map *MapManager::getMap() const
{
	return &map;
}

QList<QPointF> MapManager::getPath(const QPointF &from, const QPointF &to) const
{
	QList<QPointF> result;

	// TODO

	return result;
}
