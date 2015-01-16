/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "Mind/MapManager/Map.hpp"

Map::Map(const QJsonObject &json)
	: json(json),
	  name(json[Properties::MapName].toString()),
	  desc(json[Properties::MapDesc].toString()),
	  size(json[Properties::MapWidth].toDouble(), json[Properties::MapHeight].toDouble())
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
