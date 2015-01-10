/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once
#include <QtCore/QList>
#include <QtCore/QPointF>

#include "Mind/MapManager/Map.hpp"


class MapManager {
public:
	MapManager(const QJsonObject &json);

	const Map *getMap() const;
	QList<QPointF> getPath(const QPointF &from, const QPointF &to) const;

private:
	Map map;
};