/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QtCore/QList>
#include <QtCore/QPointF>

#include "DataManager/MapInfo.hpp"
#include "Mind/MapManager/Map.hpp"


class MapManager {
public:
	MapManager(const QJsonObject &json);
// 	MapManager(const MapInfo *mapInfo);

	const Map *getMap() const;
	QList<QPointF> getPath(const QPointF &from, const QPointF &to) const;

private:
	Map map;

// 	const MapInfo *mapInfo;
};