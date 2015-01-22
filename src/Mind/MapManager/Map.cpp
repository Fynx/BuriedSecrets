/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "Mind/MapManager/Map.hpp"

Map::Map(const QJsonObject &json)
	: json(json),
	  name(json[MapProperties::MapName].toString()),
	  desc(json[MapProperties::MapDesc].toString()),
	  size(json[MapProperties::MapWidth].toDouble(), json[MapProperties::MapHeight].toDouble())
{}

const QJsonObject &Map::getJson() const
{
	return json;
}

const QString &Map::getName() const
{
	return name;
}

const QString &Map::getDesc() const
{
	return desc;
}

const QSizeF &Map::getSize() const
{
	return size;
}
