/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "Common/Strings.hpp"
#include "Mind/MapManager/Map.hpp"


// Map::Map(const MapInfo *mapInfo)
// 	: mapInfo{mapInfo}
// {}

Map::Map(const QJsonObject &json)
	: json(json)
{}

const QJsonObject &Map::getJson() const
{
	return json;
}

QString Map::getName() const
{
	return json[Properties::MapName].toString();
}

QString Map::getDesc() const
{
	return json[Properties::MapDesc].toString();
}

// const MapInfo *Map::getMapInfo() const
// {
// 	return mapInfo;
// }
